this program, if run, will return:
  nx500 if it is run on nx500 with firmware v1.12
  nx1   if it is run on nx1   with firmware v1.41

compile with `arm-linux-gnueabi-g++ -D_FILE_OFFSET_BITS=64 -o nx-model nx-model.cpp --sysroot=../../nx500/mnt/rootfs/ libdl-2.13.so -Wl,-dynamic-linker,/lib/ld-2.13.so`
