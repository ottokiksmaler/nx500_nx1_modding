/*
 *
 *                      nx-model v1.0
 *
 * This program prints  "nx1"  if run on nx1   w/firmware v1.41 and
 *                      "nx500 if run on nx500 w/firmware v1.12
 * 
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

#include <stdio.h>

void about () {
	printf ("\
 *                                                                            \n\
 * Usage: ./nx-model                                                          \n\
 *                                                                            \n\
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
 *                                                                            \n\
 *     If you find this program useful, remember I have a lens fund that      \n\
 *     only reached about half of its target :-)                              \n\
 *                                                                            \n\
 *     goo.gl/7I67Rq      paypal: ppnx.vasile@dfgh.net                        \n\
 *                                                                            \n\
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\
\n");
}

#include <strings.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
//#include <stdbool.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <unistd.h>
//#include <sys/ptrace.h>
//#include <unistd.h>
#include <stdlib.h>
//#include <stdint.h>
//#include <ctype.h>
//#include <dirent.h>
//#include <libgen.h>

int main (int argc, char *argv[]) {
	if (argc > 1) {
		about ();
		return 0;
	}
	static char const *sModel = NULL; // nx500 or nx1
	if (sModel == NULL) {
		FILE *fd= fopen ("/etc/version.info", "r");
		if (fd != NULL) {
			char buff[200];
			fgets (buff, 200, fd);
			if (strcmp (buff, "1.12\n") == 0) {
				fgets (buff, 200, fd);
				if (strcmp (buff, "NX500\n") == 0) {
					sModel = "nx500";
				}
			} else if (strcmp (buff, "1.41\n") == 0) {
				fgets (buff, 200, fd);
				if (strcmp (buff, "NX1\n") == 0) {
					sModel = "nx1";
				}
			}
			fclose (fd);
		}
	}
	printf ("%s\n", sModel);
}
