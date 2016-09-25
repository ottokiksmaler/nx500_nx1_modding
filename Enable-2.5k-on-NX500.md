#Enabling 2.5k video on NX500

##Note: This is an old method with very low bitrate. Suggested approach is via [Vasile's](https://github.com/ottokiksmaler/nx500_nx1_modding/tree/master/video-bitrate-mods/nx-patch) or [NX-KS](https://www.facebook.com/NXKS2) modpack.

First see procedure of running shell scripts from SD card as explained here: [Running arbitrary shell scripts from SD card](https://github.com/ottokiksmaler/nx500/blob/master/Running-shell-scripts-from-SD-card.md)

In nx_cs.adj file put:
```
sys_param movie size 2560_1440_30p
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
Stream #0:1(eng): Video: none (hvc1 / 0x31637668), 2560x1440, 11280 kb/s, 29.97 fps, 29.97 tbr, 120k tbn, 120k tbc 
```
So, very low bitrate - barely usable (it was a static scene, but still).
