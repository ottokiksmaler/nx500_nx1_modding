compile with:

`
arm-linux-gnueabihf-gcc -o nxcalldyn nxcalldyn.c --sysroot=../../nx500/mnt/rootfs/ libc-2.13.so libdl-2.13.so -Wl,-dynamic-linker,/lib/ld-2.13.so
`

Sample results:
`nxcalldyn iii /usr/lib/libprefman.so pref_get_long 3 0x208`
`called /usr/lib/libprefman.so: pref_get_long(3 [0x3], 520 [0x208]) ===> 1244 [0x4dc]`


`nxcalldyn si /usr/lib/libprefman.so pref_get_name 9`
`called /usr/lib/libprefman.so: pref_get_name(9 [0x9]) ===> adj_dpc`


