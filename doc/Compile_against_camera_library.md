#Compile against existing library in camera rootfs

You need to extract and mount rootfs or copy needed files in some other manner to you computer.

You also need Samsung Open Source packages for your camera (freely available at their site) at some location (let's say ```../arm/```).

For example, we will compile against libprefman.so library existing in /usr/lib/libprefman.so on th camera root filesystem.

Our small C program is (my_prefman.c):
```
#include <stdio.h>

long int pref_get_long(int pref_id, int pref_offset);

int main(int argc, const char *argv[])
{
    printf("pref_get_long(3,0x208)=%ld\n", pref_get_long(3,0x208));
    return 0;
}
```

This program will try to emulate the call to prefman tool like this
```
[root@drime5 ~]# prefman get 3 0x208 l                              
[sysrw] in memory: 


 value = 5846 (0x000016d6) 

[root@drime5 ~]# /mnt/mmc/my_prefman          
Hello from main!
pref_get_long(3,0x208)=5846
```

To compile, put libprefman.so (or any other needed library) in your compile directory (there is a more elegant way but this works as well) and compile with:
```
arm-linux-gnueabihf-gcc -o my_prefman my_prefman.c --sysroot=../arm/ libprefman.so -Wl,-dynamic-linker,/lib/ld-2.13.so
```

Now copy the file to the SD card and start it from the telnet session to test. It works.

## The Hard Part (TM)

Is "guessing" ```long int pref_get_long(int pref_id, int pref_offset);``` for every call you want to use. It's not really guessing, but it will involve decompiling, looking at binary files, etc, the usual stuff...
