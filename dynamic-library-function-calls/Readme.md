compile with:
`arm-linux-gnueabihf-gcc -o calldyn calldyn.c --sysroot=../../nx500/mnt/rootfs/ libc-2.13.so libdl-2.13.so -Wl,-dynamic-linker,/lib/ld-2.13.so`
