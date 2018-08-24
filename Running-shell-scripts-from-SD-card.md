# Running shell scripts from SD card

How to run a shell script file:
  1. Put file named "info.tg" on the SD card root with contents "nx_cs.adj" and a newline
  2. Put file named "nx_cs.adj" (can use something else really) on the SD card root and put "shell script /mnt/mmc/test.sh" and a newline in it
  3. Put file named "test.sh" (or whatever you put up there) on SD card root and put whatever bash shell commands you want to in it. Word of caution - it's easy to make a mistake - start small and work carefully
  4. Put SD card in camera
  5. Camera to AUTO mode (IIRC it works in any mode but whatever, it's in AUTO in the Service Manual)
  6. Power on the camera and wait a bit (or a lot, it seems it's quite lazy with closing files and syncing, might do it for it by calling "sync" at the end a few times - it seems it does no actually sync every time)
  7. Power the camera off (and wait for blinking light to stop blinking if it's blinking)

For example, if you put following in test.sh
```
st > /mnt/mmc/test
```
This is what you get on the output:
```
usage: st [command] [param]
Supported bult-in commands
help readl writel dump
gpio hdmi log lcd
cap pmu clk thread
key firmware util app
leak devman stlcd bat
rtc tbm micom misc
oic dvfs adc
```
I put a "ls -laR / > /mnt/mmc/test" and it did list the whole filesystem including /proc /sys /dev /etc etc.

Presence of **info.tg** file starts the **dfmsd** daemon process (that processes the commands in that file) but it also disables the touchscreen on camera (as it overlays it's own layer on top of standard UI - that's the green dots on the left). If you want to use the touchscreen put

> killall dfmsd

in the shell file.

**Notice:** If you are having issues with empty output files, etc, it's possible the camera did not actually *sync* when it was told to (that also explains multiple syncs in various shell files on camera). When restarting the camera with new scripts always do [*the cargo cult dance*](https://en.wikipedia.org/wiki/Cargo_cult) of removing the card and battery, waiting for few seconds, reinsert the battery and then the card. Camera is actully not booting every time, it's constantly hibernating and resuming - this might throw you off when you are doing stuff to it it does not expect.
