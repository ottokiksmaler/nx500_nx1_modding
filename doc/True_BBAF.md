#True Back-Button Auto-Focus

**Currently works only on NX1**

In order to have true BBAF, we need to prevent half-press on the shutter from engaging in AF while still allowing AF-ON to do it (essentially relocate half-press to AF-ON button). 

In order to do that we need to mask the ```S1``` button so the camera does not react to it. We can do it by writing ```0x307830303030303830300a``` to file ```/sys/devices/platform/d5keys-polled/keymask``` on NX1 or ```/sys/devices/platform/d5-keys/keymask``` on NX500 (NX500 does not have an AF-ON button but I'm working on it).

We can do it with new version poker tool ([source](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/poker.c) and [binary](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/poker.c)) that can write to files as well as RAM, like this:
```
/mnt/mmc/poker /sys/devices/platform/d5keys-polled/keymask 0x0:307830303030303830300a
```

To restore functionality of S1 button do this
```
/mnt/mmc/poker /sys/devices/platform/d5keys-polled/keymask 0x0:307830303030303030300a
```

This setting does not survive reboot (warm or cold) so needs to be made persistent as a checkbox in mod_gui (https://github.com/ottokiksmaler/nx500_nx1_modding/tree/dev/mod_gui/scripts) if one is using it for the mods.
