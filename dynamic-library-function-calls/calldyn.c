#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*libFunc_iii)(int, int);
typedef char *(*libFunc_si)(int);

typedef void (*callWrapper)(char *, char *, int, const char* []);
	// int libfunc(int, int)
void call_iii(char *libPath, char *funcName, int argCount, const char *argList[]) {
	printf("called call_iii(%s, %s)\n", libPath, funcName);
}
	// char *libfunc(int)
void call_si(char *libPath, char *funcName, int argCount, const char *argList[]) {
	printf("called call_si(%s, %s)\n", libPath, funcName);
}
	// void libfunc(int)
void call_vi(char *libPath, char *funcName, int argCount, const char *argList[]) {
	printf("called call_si(%s, %s)\n", libPath, funcName);
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
	for(i=0; i<sizeof(functionList); i++) {
		if(strcmp(functionList[i].sFuncName, argv[1])==0) {
			printf("found func %s\n", argv[1]);
			break;
		}
	}
	if(i==sizeof(functionList)) printf("function not supported\n");
	return 0;
}

