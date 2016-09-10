#Removing 30 min Movie Recording Limit Without Hacking the Camera

###NOTE: This only removes 30 min limit. To have unlimited 4k/UHD on NX500 you need to hack your camera as described [here](https://github.com/ottokiksmaler/nx500_nx1_modding/tree/master/nx-on-wake) and [here](https://github.com/ottokiksmaler/nx500_nx1_modding/tree/master/video-bitrate-mods/nx-patch)

This tool is useful to remove 30 min movie recording limit on your own camera if you don't want to hack it.

This tool exists because Samsung has removed easy access to DEV menu (that originally enabled this functionality) from newest versions of firmwares.

You will need a spare SD card for this (any card, size is not important, you can reuse the card afterwards).

Instructions:
  - Download this ZIP file: [nx_rec_limit_remover.zip](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/nx_rec_limit_remover.zip?raw=true)
  - Unpack it to some spare SD card (so that there is a file **info.tg** on the root directory of the SD card, for example, the file ```E:\info.tg``` exists)
  - Put the SD card in the camera
  - Power on the camera
  - You will see series of green dots on the left side of screen (if there are no dots you made a mistake somewhere, try again)
  - After a few seconds text with following data will appear
    - Status of old limit setting (should be "30 min LIMIT")
    - Status of new limit setting (should be "NO LIMIT")
    - Whether the settings have been saved (should be "SETTINGS SAVED")
  - The text will disappear in 10 seconds and camera will restart

###IMPORTANT - This SD card will start the camera in *"Factory mode"* that has limited touchscreen (and other) functionality. The tool should disable itself after one run, but you can always remove this card (or delete file ```info.tg``` or format the card) and power on the camera.
