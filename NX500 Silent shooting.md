#NX500 - Enabling Fully Electronic Shutter (Silent)

**Does not work on NX1**

Execute needed command from telnet session or script, etc:
```
[root@drime5 ~]£ st cap capdtm setusr 117 0x00750001
UserData is set
[root@drime5 ~]£ st cap capdtm getusr 117
UserData is ADJUSTSHUTTERTYPE_ROLLING (0x750001)
[root@drime5 ~]£ st cap capdtm setusr 117 0x00750000
UserData is set
[root@drime5 ~]£ st cap capdtm getusr 117
UserData is ADJUSTSHUTTERTYPE_MECHA (0x750000)
```
ROLLING is full electronic shutter.

Findings so far:
  1. I can see no difference in image quality between ROLLING and MECHA shutter (tested up to ISO 6400, did not test 5 stop pushing of SRW and similar tests)

  2. I can see no shutter shock at any speed in ROLLING => actually clearer image

  3. Timelapse works!

  4. You can set any shutter speed you want, but if it's under 1/30s it will be 1/30s - no long exposures

  5. Rolling shutter is really taking it's time rolling - at least 30ms but can give you that "vintage fast" effect

  6. Setting does not survive reboot - not really a bad thing 

So, this is primarily useful for doing timelapses as mechanical shutter has a very finite life in number of actuations and doing longer timelapses can shorten it significantly. 
