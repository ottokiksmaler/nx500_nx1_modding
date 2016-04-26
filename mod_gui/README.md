#This is the staging area for v2 keyscan and mod_gui tool

##Changes 

###keyscan
  - if nothing for scripts dir is given it is assumed to be ```/mnt/mmc/scripts```
  - if it does not exist ```/opt/usr/devel/scripts``` is tried next - if not X_OK keyscan fails (cannot work witout scripts dir)
  - it checks if there is another instance running already - TODO - make better test
  - it checks ```{scripts}/auto/*.sh``` for executable files and executes them on start (for mods we need to run at start)
  - it checks every 1s how much time has passed since the last check - if camera went to sleep - re-run auto scripts (silent shutter needs to be reinitialized after sleep/wakeup)
  - it checks if the scripts dir is on SD card and waits 2s for it to become available, for scripts on ```/opt/usr/devel/scripts there``` is no wait (no need)

###mod_gui
  - new tool for simple button-based gui
  - it displays two columns of buttons or checkboxes defined in ```{scripts}/mod_gui_NX500.cfg``` or ```{scripts}/mod_gui_NX1.cfg``` depending on the model
  - buttons 
    - on click they will execute specified script or command
  - checkboxes 
    - on switch to ON they execute specified script (e.g. ```rolling_shutter.sh```) and copy it to ```{scripts}/auto``` directory for keyscan to find on next wakeup
    - on switch to OFF delete the file from ```{scripts}/auto``` directory and execute ```off_{script_name}``` (e.g. ```off_rolling_shutter.sh```) if it exists
  - exit from mod_gui by half-pressing the ```Shutter button``` or clicking the ```Menu``` button

###mod_gui installer
  - **under development - needs further testing**
  - GUI tool for installation - make the last parameter **install** (e.g. ```mod_gui /mnt/mmc/scripts install```)
  - available options documented on https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/mod_gui/INSTALL-HELP.md
  - Presents 6 buttons: Info/Help, install to factory mode, to SD card via BT, keyscan to camera, keyscan and scripts to camera and Quit.

###mod_gui config file format

This is a very simple file, every button/checkbox is defined by a single line. Lines starting with # and not containing | (pipe - used as separator) are ignored.

```
# This is a comment
<checkbox|button>|<Label for item>|<script name>
```

For example:
```
# Every line a new button - Label and command separated by pipe "|"
checkbox|Silent shutter|rolling_shutter.sh
checkbox|2.5k|2k5.sh
button|Focus stacking|focus_stack.sh
button|Focus buttons|focus_buttons.sh
```
This file will make mod_gui display two rows and two columns of buttons like this

| [ ] Silent shutter | [ ] 2.5k |
| --- | --- |
| Focus stacking | Focus buttons |

If the number of buttons is less than 12 the button height is 80px (6 rows, 2 columns). One can use up to 16 buttons (8 rows) and their height will be reduced to 60px.
