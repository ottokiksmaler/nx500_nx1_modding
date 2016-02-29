#Enabling 1080p 120fps video on NX500

First see procedure of running shell scripts from SD card as explained here: [Running arbitrary shell scripts from SD card](https://github.com/ottokiksmaler/nx500/blob/master/Running-shell-scripts-from-SD-card.md)

In nx_cs.adj file put:
```
sys_param movie size 1920_1080_120p
shell script /mnt/mmc/killdfmsd.sh
```

In killdfmsd.sh file put:
```
sleep 1
killall dfmsd
```

Killing dfmsd daemon enables the use of touchscreen.

Now, when you press the DEL (Trashcan / Video preview) button and enter the video mode you can see that the resolution icon id showing MJPEG (but it's not MJPEG - it's just the last icon it found when searching for the right one that does not exist).

Here is what ffmpeg says about the video stream
```
Stream #0:0(eng): Video: none (hvc1 / 0x31637668), 1920x1080, 38955 kb/s, 119.88 fps, 119.88 tbr, 120k tbn, 120k tbc
```
So, decent bitrate - very usable. To my eyes looks better than 720p video of the same scene. 

**Note:** In camera playback does not work properly.

##List of video modes available in firmware

For NX500:
  - 4096_2160_24p
  - 3840_2160_30p
  - 2560_1440_30p
  - 1920_1080_120p
  - 1920_1080_60p
  - 1920_1080_30p
  - 1920_1080_24p
  - 1920_1080_15p
  - 1280_720_120p
  - 1280_720_60p
  - 1280_720_30p
  - 640_480_60p
  - 640_480_30p 

For NX1:
  - 4096_2160_24p
  - 3840_2160_30p
  - 3840_2160_24p
  - 3840_2160_23_98p
  - 1920_1080_120p
  - 1920_1080_60p
  - 1920_1080_30p
  - 1920_1080_24p
  - 1920_1080_23_98p
  - 1920_1080_15p
  - 1280_720_60p
  - 1280_720_30p
  - 640_480_60p
  - 640_480_30p 

PAL modes (25fps based) are not declared in the firmware but are probably derived from these modes.
