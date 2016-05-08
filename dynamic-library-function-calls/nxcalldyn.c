#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*libFunc_iii)(int, int);
typedef char *(*libFunc_si)(int);

typedef void (*callWrapper)(char *, char *, int, const char* []);
	// int libfunc(int, int)
void call_iii(char *libPath, char *funcName, int argCount, const char *argList[]) {
	printf("sss\n");
	if(argCount==2) {
		int arg1=0; int arg2=0;
		if(sscanf(argList[0], "%d", &arg1)==1 && sscanf(argList[1], "%d", &arg2)==1) {
			printf("called %s: %s(%d [%#010x], %d [%#010x])\n", libPath, funcName, arg1, arg1, arg2, arg2);
		} else {
			printf("cannot interpret the arguments\n");
		}
	} else {
		printf("this function needs exactly two integer arguments\n");
	}
}

	// char *libfunc(int)
void call_si(char *libPath, char *funcName, int argCount, const char *argList[]) {
	if(argCount==1) {
		int arg1=0;
		if(sscanf(argList[0], "%d", &arg1)==1) {
			printf("called %s: %s(%d [%#010x])\n", libPath, funcName, arg1, arg1);
		} else {
			printf("cannot interpret the argument\n");
		}
	} else {
		printf("this function needs exactly one integer argument\n");
	}
}
	// void libfunc(int)
void call_vi(char *libPath, char *funcName, int argCount, const char *argList[]) {
	if(argCount==1) {
		int arg1=0;
		if(sscanf(argList[0], "%d", &arg1)==1) {
			printf("called %s: %s(%d [%#010x])\n", libPath, funcName, arg1, arg1);
		} else {
			printf("cannot interpret the argument\n");
		}
	} else {
		printf("this function needs exactly one integer argument\n");
	}
}

static struct {
	char *sLibPath;
	char *sFuncName;
	callWrapper callFunc;
	char *sFuncDesc;
} functionList[] = {
	{ "/usr/lib/libprefman.so", "pref_get_long",  &call_iii, "int pref_get_long(int, int)" },
	{ "/usr/lib/libprefman.so", "pref_get_name",  &call_si,  "char *pref_get_name(int)"    },
	{ "/usr/lib/libprefman.so", "pref_show_info", &call_vi,  "void pref_show_info(int)"    }
};

int call_library() {
	void     *handle = NULL;
	libFunc_iii func = NULL;
	handle = dlopen("/usr/lib/libprefman.so", RTLD_LAZY | RTLD_GLOBAL);
	if (handle == NULL) {
		fprintf(stderr, "Unable to open lib: %s\n", dlerror());
		return -1;
	}
	*(void **) (&func) = dlsym(handle, "pref_get_long");

	if (func == NULL) {
		fprintf(stderr, "Unable to get symbol\n");
		return -1;
	}

	printf("pref_get_long(3, 0x208) = %ld\n", (*func)(3, 0x208));
	return 0;
}

int main(int argc, const char *argv[]) {
	int i;
	int iFunctionListSize=sizeof(functionList)/sizeof(functionList[0]);
	for(i=0; i<iFunctionListSize; i++) {
		if(strcmp(functionList[i].sFuncName, argv[1])==0) {
			functionList[i].callFunc(functionList[i].sLibPath, functionList[i].sFuncName, argc-2, &argv[2]);
			break;
		}
	}
	if(i==iFunctionListSize) printf("function not supported\n");
	return 0;
}
