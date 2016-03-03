#Customizing functions of various keys

While NX1 has a solid amount of programmable keys, the NX500 is limited to just few that can perform only a small subset of operations. For example, in order to have a video preview (Movie STBY) you have to assign it to DEL (Custom/Trashcan) button but that means you cannot use a single click to switch to RAW shooting. 

This is frustrating. 

There are also some other illogical choices like:
  - Having to choose between delay timer **AND** bracketing is just silly.
  - Reseting power zoom lens to 16mm every time the camera powers on ...
  - Not being able to quickly switch from AF-S and Single-shot to AF-C and Continuous-H ...
  - ... whatever irks *you* ...

Fret not, here is the solution:
  1. Download [sd.tar](https://github.com/ottokiksmaler/nx500/blob/master/sd.tar) file
  2. Extract it to the root of the SD card (so that SD card root contains *info.tg* file and *scripts* directory)
  3. Put the card in the camera and power it on. Wait a few seconds (booting with custom scripts lasts a bit longer)
  4. Use any of the key combinations, like:
    1. Double click EV (exposure compensation button) -> switch between AF-S/S and AF-C/C-H
    2. EV+AEL (Press EV - click AEL - release EV) -> switch between SuperFine JPEG and RAW (not RAW+SF)
    3. EV+OK -> (16-50pz only) zoom to 50mm and iZoom to 2.0x
    4. EV+HalfPressShutter -> take a shot after roughly 10s (with blinking lights) - any shot including bracketing and burst
    5. EV+MOBILE -> (connect to wireless before clicking this) start telnet server and display IP address for 30s on screen

*"Wow, this is nice, but could you implement **this** shortcut?*
No. But you can :)
In scripts directory on SD card there is a bunch of shell scripts called EV_EV.sh, EV_OK.sh, EV_AEL.sh and the like. They are called when corresponding combination of keys is pressed. You can freely alter their contents (you *should* first test interactively via telnet - it's easier that way). You can also create other files for other key combinations.

Possible key combinations (shell script names) on NX500:
  - EV_EV.sh - double click EV
  - EV_MOBILE.sh
  - EV_AEL.sh
  - EV_S1.sh - EV + half press the shutter
  - EV_S2.sh - EV + full press the shutter
  - EV_OK
  - EV_UP
  - EV_DOWN
  - EV_LEFT
  - EV_RIGHT

##How does it work?

Camera finds info.tg file on SD card, executes it by executing scripts/nx_cs.adj file that in turn executes the scripts/test.sh file. test.sh file starts keyscan binary, waits a bit and kills dfmsd so we can use the touchscreen again.

##How does the keyscan binary work?

It's a simple C program that listens on two devices (/dev/event0 and /dev/event1) for key events. When it detects an event it tries executing corresponding script from provided directory, like this:

```
keyscan /dev/event0 /dev/event1 /mnt/mmc/scripts/
```

For debugging, start it from telnet session like this:
```
keyscan /dev/event0 /dev/event1 /mnt/mmc/scripts/ debug
```

##So, where's the source? How do I know it's not doing something bad?

Source is here: [keyscan.c](https://github.com/ottokiksmaler/nx500/blob/master/keyscan.c)
Compile it with: arm-linux-gnueabihf-gcc --static -o keyscan keyscan.c -s
