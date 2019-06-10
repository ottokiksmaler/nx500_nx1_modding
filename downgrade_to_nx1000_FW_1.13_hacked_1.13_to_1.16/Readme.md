# Downgrade NX1000 to body firmware version 1.13

## BEWARE - Works for my camera - might kill your camera and pets too

Newer version don't have the support for simple acces to DEV MENU, so you can use these files to downgrade to v1.13 (it will be shown as v1.16 in the Device information). Files in this directory have been HEX edited to appear as firmware v1.16 so you can upgrade to it from the current firmware (v1.15) although they contain firmware v1.13 with just the string "1.13" changed to "1.16" in nx1000.bin file. No other changes have been made.

Procedure:
 1. Download [ROM](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/downgrade_to_nx1000_FW_1.13_hacked_1.13_to_1.16/nx1000.Rom.7z?raw=true) and [BIN](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/downgrade_to_nx1000_FW_1.13_hacked_1.13_to_1.16/nx1000.bin.7z?raw=true) files and extract the files (7Zip is the compressor used)
 2. Put files to SD card root and power on the camera
 3. Go to Menu - Settings 3 - Device information - Firmware update - make sure you have a full battery - follow the instructions on screen
 4. After firmare update power off and the power on the camera in SMART (green) mode
 5. Click: DOWN, OK, UP, OK, RIGHT, trashcan and OK together
 6. Select SYSTEM PARAMETERS to enable NO LENS and disable MOVIE time limit
