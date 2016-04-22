# NX-MOD Installation Help

This script will help you install NX-MOD to your camera.

Terms: 
  - **keyscan** - a program that intercepts your keypresses on the camera and executes script files that do something
  - **scripts** - a directory that contains aforementioned scripts
  - **root filesystem** - a **read-only** filesystem present on the camera - can be made **read-write** and modified for modding needs.

There are four different options:
  1. Factory mode (limited functionality)
    - This option does not modify your camera in any way. It uses the "factory mode" of the camera to run scripts off the SD card. This mode has limited touchscreen functionality and is slightly slower in operation as the camera is doing all the debugging in the background. This process is described [here] (https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/Running-shell-scripts-from-SD-card.md).
  2. Mods and scripts on SD card
    - This option makes minimal modifications to your camera - it modifies the file /usr/sbin/bluetooth as described [here] (https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/Running_scripts_without_factory_mode_BT.md). The **keyscan** binary and **scripts** are on the SD card.
  3. Mods on camera scripts on card
    - This option makes a bit more modifications to your camera - it modifies the file /usr/sbin/bluetooth as described [here] (https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/Running_scripts_without_factory_mode_BT.md) and stores keyscan binary on the camera **root filesystem**. The **scripts** are on the SD card. This enables for faster startup of the keyscan binary 
  4. Mods and scripts on camera
    - This option makes even more modifications to your camera - it modifies the file /usr/sbin/bluetooth as described [here] (https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/Running_scripts_without_factory_mode_BT.md) and stores keyscan binary and scripts directory on the camera **root filesystem**. This enables for faster startup of the keyscan binary and persistent mods (like rolling shutter that does not survive power-off - power-on).
 
#TL;DR

Q: I just want to use the mods, what to choose?
  - A: Pick second option "Mods and scripts on SD card" 

Q: I am an advanced user, what to pick? 
  - A: Pick the third option "Mods on camera scripts on card" 
