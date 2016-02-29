#Running gdb

There are two approaches: local and remote.

##Remote gdb

Your easiest route is to use prebuilt gdb and gdbserver from [linaro](https://launchpad.net/linaro-toolchain-binaries/trunk/2012.10/+download/gcc-linaro-arm-linux-gnueabihf-4.7-2012.10-20121022_linux.tar.bz2). 
  1. You will need gdbserver from gcc-linaro-arm-linux-gnueabihf-4.7-2012.10-20121022_linux/arm-linux-gnueabihf/debug-root/usr/bin/gdbserver on the camera (SD card)
  2. You will need arm-linux-gnueabihf-gdb from gcc-linaro-arm-linux-gnueabihf-4.7-2012.10-20121022_linux/bin on your PC.
  3. On camera start /mnt/mmc/gdbserver --multi 0.0.0.0:2345
  4. On PC start gdb 

  ```
  (gdb) target extended-remote IP_OF_CAMERA:2345
  (gdb) attach 414
  Attaching to process 414
  0x00019454 in ?? ()
  or
  (gdb) set remote exec-file /mnt/mmc/whatever
  (gdb) run
  ... debug as usual ...
  ```

##Local gdb

You have to cross-compile gdb on your computer statically. Follow generic instructions just use **make LDFLAGS=-static** at the end.

Run it from telnet session and work as usual.

To not make it too easy, all binaries are stripped...
