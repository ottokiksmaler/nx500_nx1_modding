# How to Access DEV and CS Modes (and Remove Video Time Limit) - not for current firmwares

Original work was done and published by [Vasile on DPReview](http://www.dpreview.com/forums/thread/3979382).

## Acessing DEV Mode

Create file on SD card root with name **nx_dev.adj** with **smart_camera** text in it (no newline).

Boot the camera, switch to AUTO mode, press Down, OK, Up, OK, Right, EV+OK (press exposure compensation button, click OK, release exposure compensation button)

### Remove Time Limit for Video

When the DEV Menu appears, go to second option SYSTEM PARAMETER, then to (5) DISABLE MOVIE REC LIMIT. That's it. You can also control power saving features there or perform firmware update, etc. Look around but be **very careful**.

For video instructions by [Geoff CB see here](https://www.youtube.com/watch?v=gF4omWstv0c).

**On NX1 this removes all time limits. On NX500 this removes 29:59 time limits (1080@30fps and similar), limits due to other things still remain (4k, 1080@60fps, etc).**

## Accessing CS Mode

Don't do it.

Really, if you really need to disable WiFi or change BT MAC, or change shipping country - you will find needed information from service manual. I would stay clear.

That said, the procedure is the same, just the name of the file is **nx_cs.adj** and adjustment script files should have names like adjustment/nx500/7.shipment_country.adj and the like. Without those files you can only disable WiFi.
