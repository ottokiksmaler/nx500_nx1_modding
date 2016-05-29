/*
 * 
 * Copyright (C) 2016  Vasile Dumitrescu, (ppnx.vasile@dfgh.net)
 * parts Copyright (C) 2016  Otto Kiksmaler
 * uses /proc walk sample code provided by Arjun Pakrashi
 *       https://phoxis.org/author/phoxis/
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

#include <strings.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <dirent.h>
#include <libgen.h>

#include "CExeMemPatch.h"

#define BUFF_SIZE 255

#define PROC_MAX_BUF 1024
#define PROC_PID_LIST_BLOCK 32


static bool debug = false;
static bool debug_errors = true;

// ====================================================================================================================
// ====================================================================================================================
// === class CExeMemPatch ==============================================================================================
// ====================================================================================================================
// ====================================================================================================================

int CExeMemPatch::pidAttach () {
  char dev_mem_filename[BUFF_SIZE];
  debug && printf ("attached to pid: %d\n", (int)pid);
  sprintf (dev_mem_filename, "/proc/%d/mem", pid);
  int fd = open (dev_mem_filename, O_RDWR);
  if (ptrace (PTRACE_ATTACH, pid, NULL, NULL) == -1) {
     (debug || debug_errors) && printf ("Open (%s): ERROR\n", dev_mem_filename);
    return false;
  }
  if (waitpid (pid, NULL, 0) == -1) {
     (debug || debug_errors) && printf ("waitpid (%d): ERROR\n", (int)pid);
    ptrace (PTRACE_DETACH, pid, NULL, NULL);
    return false;
  }
  return fd;
}

int CExeMemPatch::pidDetach () {
  ptrace (PTRACE_DETACH, pid, NULL, NULL);
  debug && printf ("detached from pid: %d: OK\n", (int)pid);
  close (fd);
}

bool CExeMemPatch::check_if_number (const char *str) {
  int i;
  for (i=0; str[i] != '\0'; i++) if (!isdigit (str[i])) return false;
  return true;
}

pid_t CExeMemPatch::getPidFromProcessName (const char *sProcessName) {
  DIR *dirp;
  FILE *fp;
  struct dirent *entry;
  char path [PROC_MAX_BUF];
  char read_buf [PROC_MAX_BUF];
  pid_t retVal = 0;
  dirp = opendir ("/proc");
  if (dirp == NULL) {
     (debug || debug_errors) && printf ("could not open /proc/\n");
    return 0;
  }
  while ( (entry = readdir (dirp)) != NULL) {
    if (check_if_number (entry->d_name)) {
      sprintf (path, "/proc/%s/comm", entry->d_name);
        /* A file may not exist, it may have been removed.
        * dut to termination of the process. Actually we need to
        * make sure the error is actually file does not exist to
        * be accurate.
        */
      fp = fopen (path, "r");
      if (fp != NULL) {
        fscanf (fp, "%s", read_buf);
        if (strcmp (read_buf, sProcessName) == 0) {
          retVal = atoi (entry->d_name);
        }
        fclose (fp);
        if (retVal > 0) break;
      }
    }
  }
  closedir (dirp);
  return retVal;
}

off_t CExeMemPatch::getModuleOffset (const char *sTargetModule) {
  char buf[100];
  off_t retVal = 0;
  sprintf (buf, "/proc/%d/maps", pid);
  FILE *fd = fopen (buf, "r");
  if (fd != NULL) {
    unsigned int moduleStart = 0;
    char sPerms[5];
    char sCurrentModule[1024];
    char mapLineBuf[1024];
    int iReadItemCount = 0;
    while (!feof (fd)) {
      fgets (mapLineBuf, sizeof (mapLineBuf), fd);
      iReadItemCount = sscanf (mapLineBuf, "%8x-%*8x %4s %*s %*s %*s %s", 
              &moduleStart, &sPerms, &sCurrentModule);
      if (iReadItemCount == 3 && strcmp (sPerms, "r-xp") == 0 && 
              strcmp (sTargetModule, sCurrentModule) == 0) {
        retVal = (off_t) moduleStart;
        break;
      }
    }
    fclose (fd);
  }
  return retVal;
}

CExeMemPatch::CExeMemPatch (const char *sProcessName) {
  pid = getPidFromProcessName (sProcessName);
  fd = pidAttach ();
}

CExeMemPatch::~CExeMemPatch () {
  pidDetach ();
}

bool CExeMemPatch::peek (const char *sTargetModule, off_t offset, char *buffer, size_t size) {
  if (size > BUFF_SIZE) {
    (debug || debug_errors) && printf ("SIZE TOO LARGE ERROR %d > %d\n", (int)size, BUFF_SIZE);
    return false;
  }
  int i=0;
  off_t absoluteOffset = (off_t) (offset + getModuleOffset (sTargetModule));
  debug && printf ("CExeMemPatch::peek calculated absolute offset is 0x%llx\n", absoluteOffset);
  if (lseek (fd, absoluteOffset, SEEK_SET))
    if ( (i = read (fd, buffer, size)) >= 0)
      debug && printf ("CExeMemPatch::peek ok, just read %d bytes\n", i);
    else {
      (debug || debug_errors) && printf ("CExeMemPatch::peek error: %d\n", (errno));
      return false;
    }
  return true;
}

bool CExeMemPatch::poke (const char *sTargetModule, off_t offset, const char *buffer, size_t size) {
  if (size > BUFF_SIZE) {
     (debug || debug_errors) && printf ("CExeMemPatch::poke error: size too large: %d > %d\n", (int) size, BUFF_SIZE);
    return false;
  }
  int i=0;
  off_t absoluteOffset = (off_t) (offset + getModuleOffset (sTargetModule));
  debug && printf ("CExeMemPatch::poke calculated absolute offset is 0x%llx\n", absoluteOffset);
  if (lseek (fd, absoluteOffset, SEEK_SET))
    if ( (i = write (fd, buffer, size)) >= 0){
      debug && printf ("CExeMemPatch::poke OK, poked %d bytes at 0x08x\n", i, absoluteOffset);
    } else {
      (debug || debug_errors) && printf ("CExeMemPatch::poke error: %d\n", (errno));
      return false;
    }
  return true;
}

bool CExeMemPatch::pokeIf (const char *sTargetModule, off_t offset, const char *buffer_original,
                         char *buffer, size_t size) {
  if (size>BUFF_SIZE) {
    (debug || debug_errors) && printf ("CExeMemPatch::pokeif error: size too large: %d > %d\n", (int)size, BUFF_SIZE);
    return false;
  }
  char buffer_temp[BUFF_SIZE];
  if (!peek (sTargetModule, offset, buffer_temp, size)) {
    return false;
  }
  for (int i = 0; i < size; i++) {
    if (buffer_temp[i] != buffer_original[i]) {
      (debug || debug_errors) && printf ("CExeMemPatch::pokeif error: buffers not the same\n");
      return false;
    }
  }
  return poke (sTargetModule, offset, buffer, size);
}

bool CExeMemPatch::peekUint (const char *sTargetModule, off_t offset, unsigned int *val) {
  char buf[4];
  if (peek (sTargetModule, offset, buf, 4)) {
    *val = *((unsigned int *) buf);
    return true;
  }
  return false;
}
bool CExeMemPatch::pokeUint (const char *sTargetModule, off_t offset, unsigned int val) {
  return poke (sTargetModule, offset, (const char *) &val, 4);
}

bool CExeMemPatch::pokeIfUint (const char *sTargetModule, off_t offset, unsigned int prevVal, unsigned int newVal) {
  unsigned int peekVal;
  if (peekUint (sTargetModule, offset, &peekVal))
    if (peekVal == prevVal)
      return pokeUint (sTargetModule, offset, newVal);
  return false;
}

