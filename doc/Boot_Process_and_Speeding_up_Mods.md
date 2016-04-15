#NX Boot Process and how to Speed up Mods

TLDR - in order to execute immediatelly we need to modify the internal filesystems some more.

Longer version:

When a camera boots it actually wakes up from hybrid-sleep:
  - If it was just sleeping - resume from suspend to RAM - very fast (this actually happens when you turn power button to OFF and then ON)
  - If it lost power, etc - resume from suspended RAM image in partition 9 - slower (this happens when you remove the battery, etc)

Important things to keep in mind
  - We are using bluetooth as an entry hook for our mods (by altering /usr/sbin/bluetooth to call our scripts)
  - We are using keyscan binary as entry point to hacks
  - In both cases the camera will trigger Bluetooth if it was active prior to power-off
  - We cannot speed up the second option - it has to fully unpack contents to RAM and start fresh

So, whould we try to start the keyscan binary faster? Nope. The only reason we need to start the keyscan binary is because it was killed prior to sleep. It was killed since di-camera-app must unmount the SD card (after completing writing to it, etc). If we move the keyscan (and scripts for that matter) to camera's internal filesystem the camera will not kill the keyscan at all. All our mods keep running just fine - no need to restart them at all.

Modifications from telnet session:
  - Remount rootfs as read-write ```mount -o remount,rw /```
  - Edit ```/usr/sbin/bluetoothd``` to call the ```/opt/usr/devel/bin/init.sh``` (and not the one on the SD card)
  - Copy everything from /mnt/mmc/scripts/ to /opt/usr/devel/bin/ like this ```cp /mnt/mmc/scripts/* /opt/usr/devel/bin/```
  - Edit the /opt/usr/devel/bin/init.sh to call keyscan like this ```/opt/usr/devel/bin/keyscan /dev/event0 /dev/event1 /opt/usr/devel/bin/ &``` - do modify the scripts as well if they call something from SD card.
  - Just to illustrate, create a file named /opt/usr/devel/bin/EV_S1.sh with following contents:
```
echo 1 > /sys/devices/platform/leds-gpio/leds/af/brightness
sleep 1
echo 0 > /sys/devices/platform/leds-gpio/leds/af/brightness
```
  - This will light the AF assist beam for 1 second when you press EV and half-press the shutter at the same time (so you can test it **before** the bluetooth get turned on)
  - Do the sync like this ```sync;sync;sync```
  - Remount rootfs as read-only like this ```mount -o remount,ro /```
  - Power off the camera, remove the battery and reinsert it, power on the camera. It takes some time for everything to boot, wait for bluetooth symbol to appear (or turn bluetooth on if it was OFF). Power the camera down (don't remove the battery).
  - Power the camera on and press EV and half-press the shutter together - AF beam lights up even before bluetooth starts (there's virtually no delay).

Notes:
  - If you don't want to do it from telnet, wait a few days, there will be a nicer, more automated way to do it.
  - If you are starting other things (bitrate hacks, whatever) - please do check if they are running already. You can use keyscan as test as it will return 0 only if it's not already running, like this ```/opt/usr/devel/bin/keyscan /dev/event0 /dev/event1 /opt/usr/devel/bin/ && my_program```
