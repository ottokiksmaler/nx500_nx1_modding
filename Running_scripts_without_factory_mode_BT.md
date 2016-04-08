# Running Files From SD Card Without Entering the Factory Mode by Starting Bluetooth

### *Warning - this procedure WILL modify your camera internal filesystem*

### *Warning - this procedure was tested only on NX500 but there is no reason for it to not work on NX1*

That said, **it's reversible** - either by reading till the end or by simple firmware upgrade.

**This procedure runs the script file only when starting Bluetooth and every time when starting Bluetooth**

### How is this different from [WiFi approach](https://github.com/ottokiksmaler/nx500_nx1_modding/edit/master/Running_scripts_without_factory_mode.md)?

This has three benefits:
  1. If we mess up Bluetooth by not following this precisely - who cares - we are in development mode - BT does not work either way ;)
  2. We do need WiFi to fix things by using interactive telnet and not going in blind by executing scripts with no output
  3. The state of BT is kept across reboots 
    - if you don't want mods - disable BT
    - if you want mods on every power on - leave BT on - it's not using much of the battery anyway (or kill it from script)

## The Procedure

Run the standard procedure for rooting the camera and [starting the telnet server on the camera](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/Running-telnet-server-on-camera.md).

Once you have telnet access do following:

```
[root@drime5 ~]# mount -o remount,rw /
[root@drime5 ~]# cd /usr/sbin
[root@drime5 sbin]# mv bluetoothd bluetoothd.orig
[root@drime5 sbin]# vi bluetoothd
#!/bin/bash
if [ -x /opt/storage/sdcard/scripts/init.sh ];
then
  /opt/storage/sdcard/scripts/init.sh &
fi
/usr/sbin/bluetoothd.orig -d
[root@drime5 sbin]# chmod +x bluetoothd
[root@drime5 sbin]# ls -la blu*
-rwxr-xr-x 1 root root    136 Apr  8 10:50 bluetoothd
-rwxr-xr-x 1 root root 332440 Apr  8 10:38 bluetoothd.orig
[root@drime5 sbin]# sync;sync;sync
[root@drime5 sbin]# mount -o remount,ro /
```
Here is the example init.sh (now located in scripts directory on SD card not to populate SD card root with garbage):
```
#!/bin/bash
killall keyscan && sleep 1
/mnt/mmc/scripts/keyscan /dev/event0 /dev/event1 /mnt/mmc/scripts/ &
```
You can reboot the camera if you want to be extra sure changes were written to disk:
```
reboot
```

You can power off the camera now, remove info.tg file from SD card (or just rename it to info.tgx or similar). If you create the **init.sh** file in SD card directory **scripts** it will be executed **every time** (pay attention to this) you start BT on the camera. If you want to start it only once use any method to check whether it's already running (PID file, lock file, env variable, ps, etc).

## Q&A Section

### Why is this important? Why not just use old factory mode method?

When using factory mode not all functions of the camera are available (Bluetooth, full operation of touchscreen) and debugging (of sorts) is running thus degrading the performance of the camera. This method avoids those problems. There **might** be other problems, I have found none so far, but I have only done limited testing.

### How can I revert back to stock?

Two options:
  1. Reflash the firmware (run firmware upgrade procedure)
  2. Access the camera via telnet and
    ```
    mount -o remount,rw /
    cp /usr/sbin/bluetoothd.orig /usr/sbin/bluetoothd
    sync;sync;sync
    reboot
    ```

### Couldn't you make a nice point-and-click GUI for all this?

Yes I could and I will, but right now the priority is to test things out and get this in hands of people interested ASAP so we can develop from here. When we have stable and tested solution I (or someone else, this is all open after all) will make a nice GUI. Promise.

### Man... You still like talking a lot!

That's still not a question. And still yes.
