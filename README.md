#Samsung NX500 / NX1 - rooting and hacking

##About

This is a repo hosting information for those interested in altering the functionality of their Samsung NX500 and NX1 cameras.

These cameras run a full blown Linux ditribution (Tizen) with shell, X, networking stack, debugging and testing tools - the works. This enables us to alter functionality of the cameras and ... well - just play around - it's fun! Seeing xeyes on your camera is such a heart warming experience :)

Inital work was done and presented on DPReview Samsung Forum [here](http://www.dpreview.com/forums/thread/3964253) and [here](http://www.dpreview.com/forums/thread/3971805) and EOSHD [here](http://www.eoshd.com/comments/topic/19099-petition-for-samsung-nx1-hack/?do=findComment&comment=134256). Special thanks to tecnoworld who provided information on NX1.

##Status

Things that work:
  - [Enabling PTP mode on the camera](https://github.com/ottokiksmaler/nx500/blob/master/Enable-PTP-on-NX500-NX1.md)
  - [Capturing screenshots of LCD](https://github.com/ottokiksmaler/nx500/blob/master/Enable-Screenshot.md)
  - [Running arbitrary shell scripts from SD card](https://github.com/ottokiksmaler/nx500/blob/master/Running-shell-scripts-from-SD-card.md)
  - [Running a telnet server for remote access to camera](https://github.com/ottokiksmaler/nx500/blob/master/Running-telnet-server-on-camera.md)
  - [Running a FTP server on camera](https://github.com/ottokiksmaler/nx500/blob/master/Running%20FTP%20server%20on%20the%20camera.md)
  - Running a fully functional browser on camera (run **browser** from script or telnet session)
  - [Controlling the camera](https://github.com/ottokiksmaler/nx500/blob/master/Control-camera-from-command-line.md) over telnet or from scripts (two different ways) including changing modes, exposure parameters, capturing images, setting resolution and quality, etc.
  - Not a real 120fps - sorry - [**NX500** - **1920x1080 video at 120fps and ~40Mbps**](https://github.com/ottokiksmaler/nx500/blob/master/Enable-1080p-120fps-video-on-NX500.md) (already present in NX1)
  - Very low bitrate - sorry - [**NX500** - **2560x1440 video at 30fps and ~12Mbps - no crop**] (https://github.com/ottokiksmaler/nx500/blob/master/Enable-2.5k-on-NX500.md)
  - [Working with key events](https://github.com/ottokiksmaler/nx500/blob/master/Working-with-key-events.md) (detecting and sending) - also covers touch
  - Working with generic X - xeyes work, xmessage works, etc.
  - [Running debugger](https://github.com/ottokiksmaler/nx500/blob/master/Running-gdb.md) - gdb on device and gdb server on device
  - [Description of working with focus from command line](https://github.com/ottokiksmaler/nx500/blob/master/Working%20with%20focus.md)
  - [Description of working with lens](https://github.com/ottokiksmaler/nx500/blob/master/Working%20with%20lens.md)
  - [Focus buttons](https://github.com/ottokiksmaler/nx500/blob/master/focus_buttons.c) - Program that displays series of buttons on top of the screen 
    - long press (1+s) to save current focus position
    - click to restore saved focus position
    - Can be used for studio shooting, astrophotography (focus on infinity during day, recall the focus during the night), etc.
    - Precompiled binary is here: https://github.com/ottokiksmaler/nx500/blob/master/focus_buttons
  - [Focus stacking](https://github.com/ottokiksmaler/nx500/blob/master/focus_stack.c)
    - Focus on near point - press "Near"
    - Focus on far point - press "Far"
    - Click "Stack" and wait for it to finish
    - Files are in the usual place - remember to fix exposure/awb/etc as you normally would
    - Precompiled binary is here: https://github.com/ottokiksmaler/nx500/blob/master/focus_stack
    - Command line options are:
      ```focus_stack [ help | sweep | number_of_photos [ delay_between_photos [ button_height [ button_width ] ] ] ]```


##To do ...

Things that should work given time:
  - Removing video recording time limit
  - SSH on camera - client should work just fine, have to test server
  - Automatic backup - have to decide how to implement - related work
    - http://lemmster.de/auto-backup-from-nx300-via-ftp.html
    - https://cedarandthistle.wordpress.com/2014/11/01/autobackup-to-linux-from-the-samsung-nx300m/
  - Enabling additional kernel modules - should work similar to  [what's described here](http://www.lemmster.de/cross-compile-kernel-module-samsung-nx300-ubnut-14.04.html)
  - Crypto like here [NX Crypto Photography](https://sites.google.com/site/nxcryptophotography/)

Things that could work with a bit of luck
  - USB audio
  - Removing sharpening and noise reduction in video
  - Adding support for different Gamma/LUT in video on NX500 (perhaps on NX1 as well)

Not likely - but might be possible
  - No crop 4k video
  - Higher framerate 1080p or 720p (sensor can be read at 240fps but that's that - not implemented anywhere else in camera)
  - Higher bitrates for any video mode
  - Full sensor video at any rate
  - Silent shutter (fully electronic)

#Donations

Q: So, where's the **Donate** button?
A: Nowhere. Find a suitable charity and donate. If you cannot afford it, find a local charity and see if they need help in person - it will do you a world of good.
