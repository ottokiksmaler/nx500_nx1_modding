    Samsung NX1 and NX500 Bluetooth sdcard script enable/disable tool

                               v1.01

Credit goes to Otto: https://github.com/ottokiksmaler/nx500_nx1_modding

#############################################################################
#############################################################################
WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING

This script will (semi)permanently change your firmware. You can revert
the change and get your camera to original state by reflashing the 
firmware of by running he uninstall tool.

WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
#############################################################################
#############################################################################

Disclaimer: while I put great care in writing/testing this script, you
run it on your own risk. Let me repeat that: I am NOT responsible for any
consequence of running this script on your camera.

Having written that, the change is low impact and I can see no scenario
where you would see bad consequences from running this script.

                        How To - install

 1. Ensure your camera is on firmware v1.40 (NX1) or v1.11 (NX500).
 2. Unzip the archive somewhere on your PC.
 3. Copy the contents of the archive folder "install" on a SD card.
    The info.tg file should end up in the root folder of the SD card.
 4. Power off your camera.
 5. Insert the SD card you just copied the files on, in the camera.
 5. Pull your battery. Count to five and put it back in (camera will
    definitely not power up otherwise).
 6. Power up your camera (essential for the purpose of this script).
 7. Stare at your camera screen and wait for a few green dots on the
    left edge of the screen. They should appear for a very short time.
    In some instances they will not appear at all. Do not worry and count to
    ten before moving on to next step.
 8. Count to five and turn the camera off. In some instances turning it off
    may take longer than usual. Please wait until the SAMSUNG logo disappears
    and the camera is really turned off.
 9. Take your SD card out.
10. Pull your battery. Count to five and put it back in.
11. Put the SD card in your PC and verify that the info.tg file has
    been renamed to info.tg-done. This is your confirmation that the
    change was successful.
12. You can now erase the scripts folder as well as the info.tg-done file
    from the SD card since they are no longer needed.

Congratulations, your camera is now capable of running a variety of SD card 
based mods, including my bitrate mod.

It does that by attempting to run a scripts/init.sh script if it is present
on the SD card, every time camera bluetooth is turned on.

                        How To - uninstall

Follow the exact same steps as for install, except this time use the contents
of the - you guessed - uninstall folder.

PS. These instructions do not assume that you need a brain, so please try to
not use yours: follow them mechanically.
