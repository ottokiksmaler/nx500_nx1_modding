#Checking Shutter Count, Power-on Count, etc. Without Hacking the Camera

This is useful to inspect, for example, second hand camera you want to buy or just to inspect your own camera if you don't want to hack it.

You will need a spare SD card for this (any card, size is not important, you can reuse the card afterwards).

Instructions:
  - Download this ZIP file: [nxinfo.zip](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/nxinfo.zip?raw=true)
  - Unpack it to some spare SD card (so that there is a file **info.tg** on the root directory of the SD card, for example, the file ```E:\info.tg``` exists)
  - Put the SD card in the camera
  - Power on the camera
  - You will see series of green dots on the left side of screen (if there are no dots you made a mistake somewhere, try again)
  - After a few seconds text with following data will appear
    - Shutter count
    - Power-on count
    - Flash internal count
    - Flash external count
  - The text will disappear in 30 seconds

###IMPORTANT - This SD card will start the camera in *"Factory mode"* that has limited touchscreen (and other) functionality. To normally test/use the camera, remove this card (or delete file ```info.tg``` or format the card) and power on the camera.
  
