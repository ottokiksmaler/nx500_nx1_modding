# Timezone handling on the camera

**Setting time in the camera app and timestamps on the SD card work
well, you only notice the problem when accessing files via FTP/SSH.**

## Internal treatment of time(zones)

The NX1/NX500 Linux OS is hard-coded to the Korea Standard Time (KST)
zone, at UTC+9. The RTC (hardware clock) is set to the local time (the
one visible on the UI), and files are stored to the SD card with local
time as well.

However, timezone-aware applications like SSH (sftp and scp) or the FTP
server will show incorrect timestamps that are off by multiple hours,
depending on your timezone.

SSH will use UTC internally, so it will apply
both the incorrect camera timezone and your correct local timezone to
end up with weird values.

Busybox FTPd will show UTC, which might or might not be treated as local
time by your FTP client.

For example, when your PC time and the camera app are set to Berlin (UTC+1),
you'll see the following times for the same file:

```
FTP:
-rwxr-xr-x    1 0    0      8311653 Feb 27 00:32 SAM_8704.JPG
Telnet:
-rwxr-xr-x    1 root root   8311653 Feb 27 09:32 SAM_8704.JPG
SCP:
-rwxr-xr-x    1 user user   8311653 Feb 27 01:32 SAM_8704.JPG
```

on the camera:
```
[root@drime5 ~]# date
Sun Feb 27 09:36:15 KST 2022
[root@drime5 ~]# date --utc
Sun Feb 27 00:36:17 UTC 2022
# stat SAM_8704.JPG
  File: `SAM_8704.JPG'
  Size: 8311653   	Blocks: 16256      IO Block: 512    regular file
Device: b32eh/45870d	Inode: 981         Links: 1
Access: (0755/-rwxr-xr-x)  Uid: (    0/    root)   Gid: (    0/    root)
Access: 1979-12-31 00:00:00.000000000 +0900
Modify: 2022-02-27 09:32:18.000000000 +0900
Change: 2022-02-27 09:32:18.000000000 +0900
```

on the PC:
```
$ stat /tmp/SAM_8704.JPG
  File: /tmp/SAM_8704.JPG
  Size: 8311653   	Blocks: 16240      IO Block: 4096   regular file
Device: fd01h/64769d	Inode: 11551853    Links: 1
Access: (0755/-rwxr-xr-x)  Uid: ( 1000/    user)   Gid: ( 1000/    user)
Access: 1979-12-30 16:00:00.000000000 +0100
Modify: 2022-02-27 01:32:18.000000000 +0100
Change: 2022-02-27 11:18:44.907994401 +0100
 Birth: -
```

When you change the timezone from the camera UI, it will simply change
the RTC time according to the difference between the old and the new
timezone, the system timezone won't be changed.

## Quick Workaround for FTP

It's possible to set the `TZ` environment variable for Busybox to `UTC-9`
so that it will display the actual local time of the files.

In the startup file (e.g. `/opt/usr/nx-ks/EV_MOBILE.sh`) add the following
line before the `telnetd` call:

```shell
export TZ=UTC-9
```

## Properly fixing it

You can change the Linux timezone to reflect your local timezone as
follows.

**Warning: you'll have to re-do this on each Daylight Savings Time
change!**

Choose the appropriate timezone file from `/usr/share/zoneinfo/`, then
symlink it and reboot to apply:

```shell
mount / -o remount,rw
cd /etc
mv localtime localtime.bak
ln -s /usr/share/zoneinfo/Europe/Berlin localtime
mount / -o remount,ro
sync;sync;sync
reboot
```

The FTP server will still show UTC times, though. Change the `TZ` variable
according to your needs after updating the system timezone.