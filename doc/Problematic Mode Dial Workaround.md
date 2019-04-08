# Problematic Mode Dial Workaround

### TL;DR - right now works on my NX500. There will be an installable version in some future after testing, right now - use if you know what you are doing

Almost all Samsung NX sameras with mode dial develop a problem with it. This problem manifests itself as either unresponsive mode dial that does not react to certain positions or as a jittery mode dial that switches on its own. Either way - it's annoying.

The only proper solution is to send the camera to Samsung service where they replace the board and fix the dial (at least for a while?). Unfortunatelly, there are no such services on my continent so I had to find a different solution - software.

Masking the keys via ``/sys/devices/platform/d5-keys/keymask`` does not work properly because, for example, after playback the camera UI queries the state of the dial and - problems.

But, if we create a file, let's say, ``/tmp/dial_mode`` and then bind-mount it over the ``/sys/devices/platform/d5-keys/dial_mode`` the camera will happily ignore the problematic mode dial as nothing can read it now. You gotta love unix everything-is-a-file philosophy and linux sysfs implementation :)

For example, if you create ``EV_S1.sh`` file in your keyscan scripts directory (depending on the mod pack you are using it is in various places, mine is at ``/opt/usr/devel/scripts``) with following contents:
```
echo 5 > /tmp/dial_mode
mount |grep dial_mode || mount -o bind /tmp/dial_mode /sys/devices/platform/d5-keys/dial_mode
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
if ! pkill -USR1 mod_gui
then
 $DIR/mod_gui $DIR/dial_modes.cfg &
fi
```
and then create ``dial_modes.cfg`` in the same directory with following contents:
```
#DIAL_MODES
button|SCENE|/usr/bin/st key mode scene; echo 0 > /tmp/dial_mode; killall mod_gui
button|AUTO|/usr/bin/st key mode smart; echo 1 > /tmp/dial_mode; killall mod_gui
button|P|/usr/bin/st key mode p; echo 2 > /tmp/dial_mode; killall mod_gui
button|A|/usr/bin/st key mode a; echo 3 > /tmp/dial_mode; killall mod_gui
button|S|/usr/bin/st key mode s; echo 4 > /tmp/dial_mode; killall mod_gui
button|M|/usr/bin/st key mode m; echo 5 > /tmp/dial_mode; killall mod_gui
button|C|/usr/bin/st key mode custom1; echo 6 > /tmp/dial_mode; killall mod_gui
button|OFF|/bin/umount /sys/devices/platform/d5-keys/dial_mode; killall mod_gui
```
Every time you press EV and half-shutter together - you will be presented with a menu from which you can choose the mode you want. This will survive short power downs, but will not survive long power downs or battery replacement. I can make it persistent but didn't want to do it until I can test it more thoroughly.

Please do note that this is not a solution but a workaround. I first made the trigger for mode change to be EV+DIAL but if you are having issues with the dial it's best to leave it alone.

## TODOs

- [ ] Testing, testing and more testing
- [ ] NX1 anyone? I think the relevant file is at ``/sys/devices/platform/d5-keys/``
- [ ] Making it permanent (survive battery change, etc). Already have the means - turn it into a checkbox in mod_gui ``.cfg`` file
- [ ] Make it work faster with ``stapp`` - right now it takes ~2s to switch mode
- [ ] NX1 has C2 mode
- [ ] Figure out how to trigger SAS mode - is anybody actually using this?
