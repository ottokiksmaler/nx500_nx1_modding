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

#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef void (*libFunc)();
typedef int (*libFunc_iii)(int, int);
typedef char *(*libFunc_si)(int);
typedef void (*libFunc_vi)(int);

// does not handle errors - returns 0 for malformed values
unsigned int iDecHexToInt(const char *sStringVal) {
	unsigned int retVal=0;
	if(strstr(sStringVal, "0x")!=NULL) {
		sscanf(sStringVal, "%x", &retVal);
	}	else {
		sscanf(sStringVal, "%d", &retVal);
	}
	return retVal;
}

	// int libfunc(int, int)
void call_iii(libFunc func, const char *libPath, const char *funcName, int argCount, const char *argList[]) {
	if(argCount==2) {
		int arg1=iDecHexToInt(argList[0]);
		int arg2=iDecHexToInt(argList[1]);
		int retVal=((libFunc_iii)func)(arg1, arg2);
		printf("called %s: %s(%d [0x%x], %d [0x%x]) ===> %d [0x%x]\n", libPath, funcName, arg1, arg1, arg2, arg2, retVal, retVal);
	} else {
		printf("this function needs exactly two integer arguments\n");
	}
}

	// char *libfunc(int)
void call_si(libFunc func, const char *libPath, const char *funcName, int argCount, const char *argList[]) {
	if(argCount==1) {
		int arg1=iDecHexToInt(argList[0]);
		char *retVal=((libFunc_si)func)(arg1);
		printf("called %s: %s(%d [0x%x]) ===> %s\n", libPath, funcName, arg1, arg1, retVal);
	} else {
		printf("this function needs exactly one integer argument\n");
	}
}
	// void libfunc(int)
void call_vi(libFunc func, const char *libPath, const char *funcName, int argCount, const char *argList[]) {
	if(argCount==1) {
		int arg1=iDecHexToInt(argList[0]);
		((libFunc_vi)func)(arg1);
		printf("called %s: %s(%d [0x%x])\n", libPath, funcName, arg1, arg1);
	} else {
		printf("this function needs exactly one integer argument\n");
	}
}
	// void libfunc()
void call_vv(libFunc func, const char *libPath, const char *funcName, int argCount) {
	if(argCount==0) {
		func();
		printf("called %s: %s()\n", libPath, funcName);
	} else {
		printf("this function needs no argument\n");
	}
}


int call_library(const char *callType, const char *libPath, const char *funcName, int argCount, const char *argList[]) {
	void *handle = NULL;
	libFunc func = NULL;
	handle = dlopen(libPath, RTLD_LAZY | RTLD_GLOBAL);
	if (handle == NULL) {
		printf("Unable to open lib: %s\n", dlerror());
		return -1;
	}
	*(void **) (&func) = dlsym(handle, funcName);
	if (func == NULL) {
		printf("Unable to find function\n");
		return -1;
	}
  if(strcmp(callType, "iii")==0) {
		call_iii(func, libPath, funcName, argCount, argList);
	} else if(strcmp(callType, "si")==0) {
		call_si(func, libPath, funcName, argCount, argList);
	} else if(strcmp(callType, "vi")==0) {
		call_vi(func, libPath, funcName, argCount, argList);
	} else if(strcmp(callType, "vv")==0) {
		call_vv(func, libPath, funcName, argCount);
	}
	return 0;
}


// calldyn calltype libpath funcname arg1 arg2 ...
int main(int argc, const char *argv[]) {
	if(argc<=4) {
		printf("NX camera dynamic function call - nxcalldyn v1.0\n");
		printf("Copyright (C) 2016 Vasile Dumitrescu (ppnx.vasile@dfgh.net)\n");
		printf("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n");
		printf("This is free software: you are free to change and redistribute it.\n");
		printf("There is NO WARRANTY, to the extent permitted by law.\n");
		printf("\n");
		printf("Usage: nxcalldyn callType libPath funcName arg1 ...\n");
		printf("  callType is one of iii, si, vi, vv\n");
		printf("  libPath must be complete library name, including path, e.g. /usr/lib/libprefman.so\n");
	} else {
		call_library(argv[1], argv[2], argv[3], argc-4, &argv[4]);
	}
	return 0;
}
