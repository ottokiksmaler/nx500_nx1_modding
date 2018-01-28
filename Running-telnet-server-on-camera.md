#Running telnet server on camera

How to run a telnet server on camera:
  1. Put file named "info.tg" on the SD card root with contents "nx_cs.adj" and a newline
  2. Put file named "nx_cs.adj" (can use something else really) on the SD card root and put "shell script /mnt/mmc/test.sh" and a newline in it
  3. Put file named "test.sh" (or whatever you put up there) on SD card root and put following in it
```
sleep 30
/mnt/mmc/telnetd &
```
  4. Extract busybox binary from Samsung NX300 rootfs [available here](http://opensource.samsung.com/reception/receptionSub.do?method=sub&sub=F&searchValue=nx300) and save it to SD card root as **telnetd** . Alternatively, some cameras (Gear 360 v. 2017) can use buseybox for [ARM7](https://busybox.net/downloads/binaries/1.21.1/).
  5. Put SD card in camera
  5. Camera to AUTO mode (IIRC it works in any mode but whatever, it's in AUTO in the Service Manual)
  6. Power on the camera and connect to wireless network of your choice (that's the reason for *sleep 30*)
  7. Wait for telnet server to start
  8. From computer connect to the same network and search for the camera IP (e.g. nmap -sP 192.168.1.* or similar)
  9. telnet to camera (username is **root** password is not asked for)

You should see something like
```
telnet 192.168.1.44
Trying 192.168.1.44...
Connected to 192.168.1.44.
Escape character is '^]'.

************************************************************
* SAMSUNG LINUX PLATFORM *
************************************************************

drime5 login: root

[root@drime5 ~]# ps aux
USER PID %CPU %MEM VSZ RSS TTY STAT START TIME COMMAND
root 1 0.4 0.2 4684 1452 ? Ss 23:15 0:01 /sbin/init
root 2 0.0 0.0 0 0 ? S 23:15 0:00 [kthreadd]
root 3 0.0 0.0 0 0 ? S 23:15 0:00 [ksoftirqd/0]

...

root 363 0.1 0.0 0 0 ? S 23:15 0:00 [ksdioirqd/mmc1]
root 399 0.0 0.0 4696 380 ? S<s 23:16 0:00 /mnt/mmc/telnetd
root 402 0.0 0.2 2704 1352 pts/0 S<s 23:16 0:00 -sh
root 469 3.0 0.1 2664 904 pts/0 R<+ 23:20 0:00 ps aux
```
Congratulations - we have remote root.

The fun stuff is the command **st**. It's swiss army knife - it contains everything. For example, you want to take a "smart" shot?

> st cap capt smart

Work with aperture?

> st cap capt iris drive 7.1

Shoot in RAW?

> st cap capt quality raw

Help works in most things, just add help (e.g. st cap capt help).

You want to push an OK button?

> st key click ok

You can also push/release it in two steps.

How about jog dials?

> st key jog jog1_cw 

or 
> st key jog jog1_ccw

You want to touch the screen in exact coordinates?

> st key touch push/release/click 400 300

There are so many things available, just explore **st app nx capture** (for stills) or **st app nx record** (for video)...
