###mod_gui
  - new tool for simple button-based gui
  - it displays two columns of buttons or checkboxes defined in ```{scripts}/mod_gui.cfg.NX500``` or ```{scripts}/mod_gui.cfg.NX1``` depending on the model and specified config file (here ```mod_gui.cfg```)
  - buttons 
    - on click they will execute specified script or command and exit ```mod_gui```
  - checkboxes 
    - on switch to ON they execute specified script (e.g. ```rolling_shutter.sh```) and copy it to ```{scripts}/auto``` directory for keyscan to find on next wakeup
    - on switch to OFF delete the file from ```{scripts}/auto``` directory and execute ```off_{script_name}``` (e.g. ```off_rolling_shutter.sh```) if it exists
    - after that they exit ```mod_gui```
  - sub-menus - special buttons - see below
  - exit from mod_gui by half-pressing the ```Shutter button``` or clicking the ```Menu``` button

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
button|New menu|@new_menu.cfg
button|Focus stacking|focus_stack.sh
button|Focus buttons|focus_buttons.sh
```
This file will make mod_gui display two rows and two columns of buttons like this

| [ ] Silent shutter | New menu |
| --- | --- |
| Focus stacking | Focus buttons |

If one clicks on "New menu" ```mod_gui``` will try to open configuration file ```new_menu.cfg``` (notice no .NX500 at the end) and update the window contents accordingly.

If the number of buttons is less than 12 the button height is 80px (6 rows, 2 columns). One can use up to 24 buttons (8 rows) and their height will be reduced to 40px.
