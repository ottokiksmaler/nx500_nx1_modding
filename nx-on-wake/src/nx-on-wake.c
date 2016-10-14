/*
 * Copyright (C) 2016  Vasile Dumitrescu, (ppnx.vasile@dfgh.net)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>
#include <string.h>

int debug = 0;

void about () {
  printf ("\
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
  * Copyright (C) 2016 Vasile Dumitrescu (ppnx.vasile@dfgh.net)\n\
  *\n\
  * License GPLv3+: GNU GPL ver. 3 or later <http://gnu.org/licenses/gpl.html>\n\
  * This is free software: you are free to change and redistribute it.\n\
  * There is NO WARRANTY, to the extent permitted by law.\n\
  *\n\
  * Usage: nx-on-wake\n\
  *\n\
  *       when run, it will daemonize and monitor for\n\
  *       SD card mount events.\n\
  *       When the SD card is mounted, it will \n\
  *\n\
  *       if /opt/storage/sdcard/nx-on-wake/on-wake exists, it will run it\n\
  *       else if /opt/usr/nx-on-wake/on-wake exists, it will run it\n\
  *\n\
  *       NB. it will run either of the above but NEVER both\n\
  *\n\
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
  *\n\
  *     If you find this program useful, remember I have a lens fund that\n\
  *     could use some help from you :-)\n\
  *\n\
  *     goo.gl/7I67Rq      paypal: ppnx.vasile@dfgh.net\n\
  *\n\
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
  \n");
}

// check if file can be found
int findFile (char *filename) {
  int file = open(filename, O_RDONLY, 0666);
  if (file > 0) {
    close (file);
    return 1;
  }
  return 0;
}

  // returns 1 if there's another instance running
int isDoubleStart () {
  int pidFile = open("/tmp/nx-on-wake.pid", O_CREAT | O_RDWR, 0666);
  if (pidFile && flock(pidFile, LOCK_EX | LOCK_NB)) return 1;
  return 0;
}

  // requires a FILE pointer to opened /proc/mounts
  // returns 1 if SD is mounted (by looking into /proc/mounts)
int isSdMounted (FILE *procMountsFile) {
    // go to beginning of /proc/mounts
  fseek (procMountsFile, 0, SEEK_SET);
  char line[256] = "";  // enough for reading a line
    // read lines from /proc/mounts until EOF reached
  while (fgets(line, 256, procMountsFile) != NULL) {
    char *sep = strstr(line, " ");
    if (sep != NULL) {
      *sep = '\0';
    } else {
      debug && system ("echo nx-on-wake: failed to parse /proc/mounts >/dev/kmsg");
      break;
    }
    char *source = line;
    char *target = sep + 1;
    sep = strstr(target, " ");
    if (sep != NULL) {
      *sep = '\0';
    } else {
      debug && system ("echo nx-on-wake: failed to parse /proc/mounts >/dev/kmsg");
      break;
    }
    if (!strcmp(source, "/dev/mmcblk1p1") &&
        !strcmp(target, "/opt/storage/sdcard")) {
      return 1;
    }
  }
  return 0;
}

int main (int argc, char *argv[]) {
  if (argc == 2) {
    if (strcmp(argv[1], "debug") == 0) {
      debug = 1;
    } else {
      about ();
      return 0;
    }
  }
  // never run two instances
  if (isDoubleStart ()) return 255;

  // daemonize me
  if (daemon (0, 0) != 0) return 254;

  debug && system ("echo nx-on-wake: started >/dev/kmsg");
  
  char *runFileOpt = "/opt/usr/nx-on-wake/on-wake";
  char *runFileSD = "/opt/storage/sdcard/nx-on-wake/on-wake";

  FILE *mfile = fopen("/proc/mounts", "r");
  int mfd = fileno(mfile);

  int sdMounted = 0;
  struct pollfd pfd;
  int pollReturnValue;
  pfd.fd = mfd;
  pfd.events = POLLERR | POLLPRI;
  pfd.revents = 0;
    // poll forever for changes to /proc/mounts
  while ((pollReturnValue = poll(&pfd, 1, -1)) >= 0) {
    if (pfd.revents & POLLERR) {
        // this will also detect unmounts so make sure you only run when 
        // SD card is mounted
      if (isSdMounted (mfile)) {
        if (sdMounted) {
            // sdcard was already mounted.
            // don't run on-wake again.
          continue;
        }
        sdMounted = 1;
          // running SD file FIRST is a safety measure: if for any reason
          // the /opt/usr/nx-on-wake is messed up, it can be overridden
          // by putting something on the SD card that will bring back control
        if (findFile (runFileSD)) {
          debug && system ("echo nx-on-wake: will run SD file >/dev/kmsg");
          system (runFileSD);
        }
        else if (findFile (runFileOpt)) {
          debug && system ("echo nx-on-wake: will run Opt file >/dev/kmsg");
          system (runFileOpt);
        } else {
          debug && system ("echo nx-on-wake: no file to run>/dev/kmsg");
        }
      } else {
          // sdcard is not mounted
        sdMounted = 0;
      }
    }
    pfd.revents = 0;
  }
}
