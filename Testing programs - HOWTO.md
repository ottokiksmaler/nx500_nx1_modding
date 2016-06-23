#How to test programs without installing them to your camera

**Note:** This assumes you have already modded your camera by installing [Vasile's master mod](https://github.com/ottokiksmaler/nx500_nx1_modding/tree/master/nx-on-wake) and [Vasile's mod pack](https://github.com/ottokiksmaler/nx500_nx1_modding/tree/master/video-bitrate-mods/nx-patch).

How to use telnet to debug and test programs:
  - Put required program on SD card (for example save https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/mod_gui/mod_gui?raw=true as "mod_gui" and copy it to SD card on your PC)
  - Put SD card in the camera
  - Start the camera
  - Start WiFi on camera (for example from pull down menu or from normal menu) and connect to the same WiFi network your PC is connected
  - start Vasile's GUI Menu (EV doubleclick) and select "telnet" from the menu 
  - It should now display IP address of your camera - write it down (or memorize, it will be different only in last number from your PC, for example if PC is 192.168.1.56 camera will be 192.168.1.73 or similar)
  - Start  telnet on PC - either by opening command prompt and typing "telnet 192.168.1.73" (with correct IP address) or from some GUI program like PuTTY (http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html) just remember to enter correct IP address and select "Telnet" as protocol (port will become 23)
  - You will see login prompt, enter "root" as username, you will not be asked for password

This is how it looks for me (ignore different directory for mod_gui, etc):
```
telnet 192.168.43.194
Trying 192.168.43.194...
Connected to 192.168.43.194.
Escape character is '^]'.


************************************************************
*                 SAMSUNG LINUX PLATFORM                   *
************************************************************


drime5 login: root
[root@drime5 ~]# /mnt/mmc/mod_gui /opt/usr/devel/scripts/ debug
Scripts:/opt/usr/devel/scripts/ Configuration file:
Configuration file: /opt/usr/devel/scripts//mod_gui.cfg.NX500
Model: NX500
Release: 1.12
Running MOD_GUI
CONFIG: Silent shutter  rolling_shutter.sh
CONFIG: Lapse   mod_lapse
CONFIG: Focus stacking  focus_stack
CONFIG: Focus buttons   focus_buttons
CONFIG: Peaking ON      peaking.sh
CONFIG: DC->2k5 2k5.sh
Auto execute: /opt/usr/devel/scripts//auto/rolling_shutter.sh
Debug ON
Key: XF86PowerOff
Exiting the app.
```
 - From there you should have access to command line interface of your camera and be able to execute anything you want.
 - Try executing "/mnt/mmc/mod_gui  /opt/usr/nx-on-wake/main debug" and watch the output. This will display you the normal GUI menu you expect. Now, when you click anything the program should print the key code and exit (like "Key: F6")
 - You now have to restart it with "/mnt/mmc/mod_gui  /opt/usr/nx-on-wake/main debug" again for another key. You should test what happens when you switch to C1, C2 and Power-Off (as I don't have C1 and C2 key and power off works for me).

Same thing applies to other tools you would like to test, new versions of focus_stacking, etc.
If you need further assistance don't hesitate to ask.
