/*
 *
 *                      nx-patch v4.0
 *
 * This program will ONLY run on nx1 firmware v1.41 and nx500 firmware v1.12
 * 
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
 * Usage: ./nx-patch camera:from:to [...]                                     \n\
 *                                                                            \n\
 * Multiple argument triplets are supported as long as they are separated by  \n\
 * white space.                                                               \n\
 *                                                                            \n\
 *   camera = one of nx1, nx500                                               \n\
 *                                                                            \n\
 *   from   = one of pro1, pro2, pro3                                         \n\
 *                   hq1, hq2, hq3, hq4, hq5, hq6, hq7, hq8                   \n\
 *                   nq5, nq6, nq7, nq8, other                                \n\
 *                   DC, UHD, FHD, HD, VGA, 2k5                               \n\
 *                                                                            \n\
 * Please refer to the enclosed .png picture for an illustration of what each \n\
 * bitrate and resolution slot corresponds to.                                \n\
 * NB I made myself the <other> slot for the extra 2k5 video resolution       \n\
 *    that is enabled by sys_param movie size 2560_1440_30p [see github]      \n\
 *                                                                            \n\
 *   to     = a bitrate, expressed in Mbps, e.g. 123 for 123,000,000 bps, or  \n\
 *            a target resolution: toDC, toUHD, toFHD, toHD, toVGA, to2k5     \n\
 *                                                                            \n\
 * Arguments are case-insensitive - you can use Uhd, UHd, uHD, UHD etc.       \n\
 *                                                                            \n\
 * The program is safe to run on any of the supported cameras and it will     \n\
 * intelligently apply only what makes sense. For example:                    \n\
 *      ./nx-patch nx500:DC:to2k5 will work on nx500 but not on nx1           \n\
 *      ./nx-patch nx1:vga:121 will set the nx1's vga bitrate with 121Mbps    \n\
 *      ./nx-patch nx500:hd:78 will do nothing since you mixed                \n\
 *                 resolution with bitrate                                    \n\
 *      ./nx-patch nx500:HD:toVGA nx1:DC:toUHD nx1:pro2:150 will detect       \n\
 *                 the camera on which it runs and                            \n\
 *                 will only apply matching patches                           \n\
 *                                                                            \n\
 * Freebies: every time the program is run, it will, additionally:            \n\
 *   - enable the DEV menu without the special file on the SD card            \n\
 *        NB you still need to do the key dance to activate it                \n\
 *   - kill nx500 UHD/DC 15 min recording limit                               \n\
 *   - annihilate nx500 FHD/50p and FHD/60p 25 min recording limit            \n\
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
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <unistd.h>
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

// returns NULL if unsupported
const char *getCameraModel () {
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
	debug && printf ("getCameraModel found %s\n", sModel);
	return sModel;
}

const char *dicamapp = "/usr/apps/com.samsung.di-camera-app/bin/di-camera-app";
const char *mmlibmov = "/usr/lib/libmmutil_movie.so.0.0.0";

unsigned long long bitRateOpCodes (unsigned int targetBitrateMbps, int regNum) {
	unsigned int bitLo = targetBitrateMbps*1000000 & 0xffff;
	unsigned int bitHi = targetBitrateMbps*1000000 >> 16;
	debug && printf ("bitRateOpCodes bitLo = 0x%08x, bitHi = 0x%08x\n", bitLo, bitHi);
	unsigned int encodedValueLo = (bitLo >> 12) + ( (bitLo & 0x0800) >> 1) 
			+ ( (bitLo & 0xFF) << 16) + ( (bitLo & 0x700) << 20);
	unsigned int encodedValueHi = (bitHi >> 12) + ( (bitHi & 0x0800) >> 1) 
			+ ( (bitHi & 0xFF) << 16) + ( (bitHi & 0x700) << 20);
	debug && printf ("bitRateOpCodes encodedValueLo = 0x%08x, encodedValueHi = 0x%08x\n", 
									 encodedValueLo, encodedValueHi);
	unsigned int emptyInstructionLo = 0x0000F240;
	unsigned int emptyInstructionHi = 0x0000F2C0;
	unsigned long long armInstructionLo = emptyInstructionLo | (regNum << 24) | encodedValueLo;
	unsigned long long armInstructionHi = emptyInstructionHi | (regNum << 24) | encodedValueHi;
	debug && printf ("bitRateOpCodes armInstructionLo = 0x%016llx, armInstructionHi = 0x%016llx\n", 
										armInstructionLo, armInstructionHi);
	return armInstructionLo | (armInstructionHi << 32);
}

	// assumes camera has already been validated
void patchBitRate (CExeMemPatch *patchExe, const char *sModuleName, const char *sNewVal, 
											const char *sCamera, unsigned int offsets[], int offsetCount, int regNo) {
	debug && printf ("patchBitRate %s, %s, %s\n", sCamera, sModuleName, sNewVal);
	if (debug_errors && offsetCount != 2) {
		printf ("patchBitRate error: too many locations to patch\n");
		return;
	}
	unsigned int rateMbps = (unsigned int) strtol (sNewVal, NULL, 10);
	if (rateMbps > 0) {
		unsigned long long opCodes = bitRateOpCodes (rateMbps, regNo);
		if (strcasecmp (getCameraModel (), sCamera) == 0) {
			patchExe->pokeUint (sModuleName, (off_t) offsets[0], (unsigned int) (opCodes & 0xffffffff));
			patchExe->pokeUint (sModuleName, (off_t) offsets[1], (unsigned int) (opCodes >> 32));
		}
	} else {
		 (debug || debug_errors) && printf ("cannot interpret bit rate: %s\n", sNewVal);
	}
}

void patchResolution (CExeMemPatch *patchExe, const char *sModuleName, const char *sNewVal, 
											const char *sCamera, unsigned int offsets[], int offsetCount, int regNo) {
	debug && printf ("patchBitRate %s, %s, %s\n", sCamera, sModuleName, sNewVal);
	if (debug_errors && offsetCount != 2) {
		printf ("patchBitRate error: too many locations to patch\n");
		return;
	}
	static struct vMO {
		const char *sCamera;
		const char *sVideoModeTarget;
		unsigned int instruction1;
		unsigned int instruction2;
	} videoModeOpcodes[] = {
		{ "nx500", "toDC",  0xE3A08E87, 0xE3A0AA01 },
		{ "nx500", "toUHD", 0xE3A08E87, 0xE3A0AC0F },
		{ "nx500", "toFHD", 0xE3008438, 0xE3A0AD1E },
		{ "nx500", "toHD",  0xE3A08E2D, 0xE3A0AC05 },
		{ "nx500", "toVGA", 0xE3A08E1E, 0xE3A0AD0A },
		{ "nx500", "to2K5", 0xE3A08E5A, 0xE3A0AC0A },
		{ "nx1",   "toDC",  0xE3A06E87, 0xE3A0AA01 },
		{ "nx1",   "toUHD", 0xE3A06E87, 0xE3A0AC0F },
		{ "nx1",   "toFHD", 0xE3006438, 0xE3A0AD1E },
		{ "nx1",   "toHD",  0xE3A06E2D, 0xE3A0AC05 },
		{ "nx1",   "toVGA", 0xE3A06E1E, 0xE3A0AD0A }
	};
	int i;
	for (int i = 0; i < sizeof (videoModeOpcodes) / sizeof (vMO); i++) {
			// if the target video code makes sense for the camera
		if (strcasecmp (sCamera, videoModeOpcodes[i].sCamera) == 0 && 
					strcasecmp (sNewVal, videoModeOpcodes[i].sVideoModeTarget) == 0) {
			patchExe->pokeUint (sModuleName, (off_t) offsets[0], videoModeOpcodes[i].instruction1);
			patchExe->pokeUint (sModuleName, (off_t) offsets[1], videoModeOpcodes[i].instruction2);
		}
	}
	if (debug_errors && i == sizeof (videoModeOpcodes) / sizeof (vMO)) {
		printf ("patchBitRate error: unknown or unsupported target resolution\n");
	}
}

void permaPatches (CExeMemPatch *emp) {
	static struct pPL {
		const char *sModel;
		const char *sModule;
		unsigned int offset;
		unsigned int patch;
	} permaPatchesList[] = {
		{ "nx500", dicamapp, 0x0dc330, 0x00000000 }, //UHD/DC  15 min rec limit
		{ "nx500", dicamapp, 0x0dc340, 0x00000000 }, //FHD/60p 25 min rec limit
		{ "nx500", dicamapp, 0x242124, 0xe3500001 }, //DEV menu patch #1
		{ "nx500", dicamapp, 0x242134, 0xe3500001 }, //DEV menu patch #2
		{ "nx500", dicamapp, 0x262528, 0xe3500001 }, //DEV menu patch #3
		{ "nx500", dicamapp, 0x262538, 0xe3500001 }, //DEV menu patch #4
		{ "nx1",   dicamapp, 0x2b9d80, 0xe3500001 }, //DEV menu patch #1
		{ "nx1",   dicamapp, 0x2b9d70, 0xe3500001 }  //DEV menu patch #2
	};
	int i = 0;
	for (i = 0; i < sizeof (permaPatchesList)/sizeof (pPL); i++)
		if (strcmp (permaPatchesList[i].sModel, getCameraModel ()) == 0)
			emp->pokeUint (permaPatchesList[i].sModule, permaPatchesList[i].offset, 
										permaPatchesList[i].patch);
	debug && printf ("permaPatches for this camera: %d\n", i);
}

#define MAX_OFFSETS 2
static struct pS {
	const char *sCamera;
	const char *sTarget;
	const char *sModuleName;
	int offsetCount;
	unsigned int offsets[MAX_OFFSETS];
	int regNo;
	void (*patchFunction) (CExeMemPatch *, const char *, const char *, 
												 const char *, unsigned int [],int, int);
} patchSlots[] = {                                                              
	{ "nx1",   "pro1",  mmlibmov, 2, {   0x09d8,   0x09dc }, 3,    patchBitRate },
	{ "nx1",   "pro2",  mmlibmov, 2, {   0x0a20,   0x0a24 }, 3,    patchBitRate },
	{ "nx1",   "hq1",   mmlibmov, 2, {   0x0832,   0x083a }, 3,    patchBitRate },
	{ "nx1",   "hq2",   mmlibmov, 2, {   0x092e,   0x0936 }, 3,    patchBitRate },
	{ "nx1",   "hq3",   mmlibmov, 2, {   0x0a30,   0x0a38 }, 3,    patchBitRate },
	{ "nx1",   "hq4",   mmlibmov, 2, {   0x0954,   0x0966 }, 3,    patchBitRate },
	{ "nx1",   "hq5",   mmlibmov, 2, {   0x095c,   0x096e }, 3,    patchBitRate },
	{ "nx1",   "hq6",   mmlibmov, 2, {   0x098c,   0x099e }, 3,    patchBitRate },
	{ "nx1",   "hq7",   mmlibmov, 2, {   0x0994,   0x09a6 }, 3,    patchBitRate },
	{ "nx1",   "nq4",   mmlibmov, 2, {   0x0950,   0x0962 }, 2,    patchBitRate },
	{ "nx1",   "nq5",   mmlibmov, 2, {   0x0958,   0x096a }, 2,    patchBitRate },
	{ "nx1",   "nq6",   mmlibmov, 2, {   0x0988,   0x099a }, 2,    patchBitRate },
	{ "nx1",   "nq7",   mmlibmov, 2, {   0x0990,   0x09a2 }, 2,    patchBitRate },
	{ "nx1",   "DC",    mmlibmov, 2, { 0x10c21c, 0x10c220 }, 0, patchResolution },
	{ "nx1",   "UHD",   mmlibmov, 2, { 0x10c24c, 0x10c250 }, 0, patchResolution },
	{ "nx1",   "FHD",   mmlibmov, 2, { 0x10c228, 0x10c22c }, 0, patchResolution },
	{ "nx1",   "HD",    mmlibmov, 2, { 0x10c234, 0x10c238 }, 0, patchResolution },
	{ "nx1",   "VGA",   mmlibmov, 2, { 0x10c240, 0x10c244 }, 0, patchResolution },
	{ "nx500", "pro1",  mmlibmov, 2, {   0x0a04,   0x0a08 }, 0,    patchBitRate },
	{ "nx500", "pro2",  mmlibmov, 2, {   0x09fa,   0x09fe }, 0,    patchBitRate },
	{ "nx500", "pro3",  mmlibmov, 2, {   0x0a64,   0x0a68 }, 0,    patchBitRate },
	{ "nx500", "hq1",   mmlibmov, 2, {   0x0962,   0x096a }, 3,    patchBitRate },
	{ "nx500", "hq2",   mmlibmov, 2, {   0x08f0,   0x08f8 }, 3,    patchBitRate },
	{ "nx500", "hq3",   mmlibmov, 2, {   0x0a50,   0x0a58 }, 3,    patchBitRate },
	{ "nx500", "hq4",   mmlibmov, 2, {   0x0920,   0x0928 }, 3,    patchBitRate },
	{ "nx500", "hq5",   mmlibmov, 2, {   0x09d0,   0x09e2 }, 3,    patchBitRate },
	{ "nx500", "hq6",   mmlibmov, 2, {   0x09d8,   0x09ea }, 3,    patchBitRate },
	{ "nx500", "hq7",   mmlibmov, 2, {   0x0998,   0x09aa }, 3,    patchBitRate },
	{ "nx500", "hq8",   mmlibmov, 2, {   0x09a0,   0x09b2 }, 3,    patchBitRate },
	{ "nx500", "nq4",   mmlibmov, 2, {   0x091c,   0x0924 }, 0,    patchBitRate },
	{ "nx500", "nq5",   mmlibmov, 2, {   0x09cc,   0x09de }, 0,    patchBitRate },
	{ "nx500", "nq6",   mmlibmov, 2, {   0x09d4,   0x09e6 }, 0,    patchBitRate },
	{ "nx500", "nq7",   mmlibmov, 2, {   0x0994,   0x09a6 }, 0,    patchBitRate },
	{ "nx500", "nq8",   mmlibmov, 2, {   0x099c,   0x09ae }, 0,    patchBitRate },
	{ "nx500", "other", mmlibmov, 2, {   0x097c,   0x0980 }, 0,    patchBitRate },
	{ "nx500", "DC",    dicamapp, 2, { 0x0dc3ec, 0x0dc3f0 }, 0, patchResolution },
	{ "nx500", "UHD",   dicamapp, 2, { 0x0dc428, 0x0dc42c }, 0, patchResolution },
	{ "nx500", "FHD",   dicamapp, 2, { 0x0dc404, 0x0dc408 }, 0, patchResolution },
	{ "nx500", "HD",    dicamapp, 2, { 0x0dc410, 0x0dc414 }, 0, patchResolution },
	{ "nx500", "VGA",   dicamapp, 2, { 0x0dc41c, 0x0dc420 }, 0, patchResolution }, 
};

#define BUF_TRIPLET_MEMBER 20
void processTriplet (CExeMemPatch *emp, const char *sTriplet) {
	char sTripletCopy[BUF_TRIPLET_MEMBER * 3 + 3];
	strncpy (sTripletCopy, sTriplet, BUF_TRIPLET_MEMBER * 3 + 2);
	char sCamera[BUF_TRIPLET_MEMBER] = "";
	char sFrom[BUF_TRIPLET_MEMBER] = "";
	char sTo[BUF_TRIPLET_MEMBER] = "";
	char *lastTok = NULL;
	lastTok = strtok (sTripletCopy, ":");
	strncpy (sCamera, lastTok, BUF_TRIPLET_MEMBER-1);
  lastTok = strtok (NULL, ":");
	if (lastTok != NULL) {
		strncpy (sFrom, lastTok, BUF_TRIPLET_MEMBER-1);
		lastTok = strtok (NULL, ":");
	}
	if (lastTok != NULL) {
		strncpy (sTo, lastTok, BUF_TRIPLET_MEMBER-1);
	}
	if (sCamera[0] != '\0' && sFrom[0] != '\0' && sTo[0] != '\0') {
		for (int i = 0; i < sizeof (patchSlots) / sizeof (pS); i++) {
			debug && printf ("processTriplet processing sCamera=%s, sFrom=%s, sTo=%s\n",sCamera, sFrom, sTo);
			if (strcasecmp (sCamera, patchSlots[i].sCamera) == 0 &&
				  strcasecmp (sFrom, patchSlots[i].sTarget) == 0)
				(*patchSlots[i].patchFunction) (emp, patchSlots[i].sModuleName, sTo, patchSlots[i].sCamera,
																				patchSlots[i].offsets, patchSlots[i].offsetCount, 
																				patchSlots[i].regNo);
		}
	}
}


int main (int argc, char *argv[]) {
	if (argc == 1) {
		about ();
		return 0;
	}
	CExeMemPatch emp ("di-camera-app");
	permaPatches (&emp);
	for (int i=1; i < argc; i++) {
		processTriplet (&emp, argv[i]);
	}
}
