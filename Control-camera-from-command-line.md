#Controlling the camera from command line or shell

There are two different ways to accomplish this goal:
  1. By using **st** command from command line or script
  2. By using **dfms** commands

##The *st* way

There is a command named **st** on the camera - it's a veritable swiss army knife. It can control many parameters of the camera, simulate key or touch events, etc.
```
st cap capt smart 
st cap capt iris drive 7.1 
```

You can use any of the st commands available and documented in part here: [ST Commands](https://github.com/ottokiksmaler/nx500/blob/master/ST%20Commands.md)

##The *dfms* way

First step is to have dfmsd running on the camera. This also disables the touchscreen operation as it overlays the screen with 8 lines of green text (you can see dots on the left - these are the lines, they just contain "." by default).

You can start dfmsd in three different modes: waiting for commands over USB (still needs to be done), reading from provided script (this is the basis for all the hacks here) and in test mode (-t switch) for interactive use with dfmstool.

**Example**

```
[root@drime5 ~]# dfmsd -t &
[1] 420
[root@drime5 ~]# [SYS_DFMS  ] Launched dfmsd daemon with test mode ... 
[root@drime5 ~]# dfmstool -s 'osd string 7 Hello World!' 
[root@drime5 ~]# dfmstool -s 'osd string 8 Take care with ! and bash...' 
```
This will display the message on screen.
From there on you can use any of the dfms commands available and documented in part here: [DFMS Commands](https://github.com/ottokiksmaler/nx500/blob/master/DFMS%20Commands.md)
When you've had enough and want your touchscreen functionality back:
```
[root@drime5 mmc]# killall dfmsd
[SYS_DFMS  ] dfms-server: thread exited 
[SYS_DFMS  ] dfms-server: thread terminated. 
[SYS_DFMS  ] dfms-osd: thread exited 
[SYS_DFMS  ] program exited. 
```



