# Running Files From SD Card Without Entering the Factory Mode by Starting WiFi

**NEW - see superior [Bluetooth approach] (https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/Running_scripts_without_factory_mode_BT.md)**

### *Warning - this procedure WILL modify your camera internal filesystem*

### Warning - this procedure was tested only on NX500 and seems to *not work on NX1*

That said, **it's reversible** - either by reading till the end or by simple firmware upgrade.

**This procedure runs the script file only when starting WiFi and every time when starting WiFi**

## The Procedure

Run the standard procedure for rooting the camera and [starting the telnet server on the camera](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/Running-telnet-server-on-camera.md).

Once you have telnet access do following:

```mount -o remount,rw /```

This will remount your root partition in read-write mode (it's in read only mode previously).

Now we edit the script file executed during starting the WiFi:

```vi /usr/sbin/wpa_supp.sh```

Modify file by adding following lines:

```
...
start()
{
# MODIFICATION START
if [ -f /mnt/mmc/run.sh ];
then
  /mnt/mmc/run.sh &
fi
#MODIFICATION END

#       /usr/sbin/wpa_supplicant -u -t -B -d -Dwext
        /usr/sbin/wpa_supplicant -u -t -B -d -Dnl80211 -e /opt/var/lib/wifi/entropy.bin
}
...
```

When you try to save the file use: 

ESC : wq!

The file is read-only in filesystem so we have to force vi to save it (so ! at the end)

Do the sync-dance:
```
sync;sync;sync
```
And reboot the camera:
```
reboot
```

You can power off the camera now, remove info.tg file from SD card (or just rename it to info.tgx or similar). If you create the **run.sh** file in SD card root it will be executed **every time** (pay attention to this) you start Wi-Fi on the camera. If you want to start it only once use any method to check whether it's already running (PID file, lock file, env variable, ps, etc).

## Q&A Section

### Why is this important? Why not just use old factory mode method?

When using factory mode not all functions of the camera are available (Bluetooth, full operation of touchscreen) and debugging (of sorts) is running thus degrading the performance of the camera. This method avoids those problems. There **might** be other problems, I have found none so far, but I have only done limited testing.

### Can we make this *permanent*? Like in not having tu trigger it via WiFi?

Yes, by finding something else that gets started and modifying it. Making a wrapper around **/usr/bin/bt-service** would, IMHO, be the best approach as it would allow us to control whether we want it on or not and even if we mess it up it's still fixable wihtout huge penalty (Bluetooth Schmoetooth).

### How can I revert back to stock?

Two options:
  1. Reflash the firmware (run firmware upgrade procedure)
  2. Repeat the procedure but just remove the added lines :)

### Couldn't you make a nice point-and-click GUI for all this?

Yes I could and I will, but right now the priority is to test things out and get this in hands of people interested ASAP so we can develop from here. When we have stable and tested solution I (or someone else, this is all open after all) will make a nice GUI. Promise.

### Man... You really like talking a lot!

That's not a question. And yes.
