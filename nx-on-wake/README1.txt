                  Samsung NX1 and NX500 nx-on-wake

                               v1.01

     Copyright (C) 2016  Vasile Dumitrescu, (ppnx.vasile@dfgh.net)

     popup_ok, popup_entry and popup_timeout Copyright (C) 2016
         Otto Kiksmaler (https://github.com/ottokiksmaler)

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

                          CHANGE LOG

Version 1.01 - 2016-06-13
  - updated README: added requirement to set power save to 30 min 
    and display save to off.
  - also removed duplicate definition of "satellite" mods

Version 1.0 - 2016-06-12
  - initial version
  
                          DESCRIPTION
                          
   This is a one-time MASTER mod, which will free you from depending on
   bluetooth for any "satellite" mods.
   
   NB. by "satellite" mods I mean mods built to take advantage of this new mod
       loading architecture.
   
   The mod will ensure that every time the camera is started (cold or warm,
   i.e. with or without battery pull), the camera will:
     (a) if there's a file on the SD card named /nx-on-wake/on-wake, it will
         attempt to run it (and only it - nothing else). To be clear, I am
         talking about having a folder called nx-on-wake in the root of the
         SD card, and that inside it there's a file called on-wake with
         no extension.
     (b) ONLY if there's NO on-wake file on the SD card, the mod will try
         to run a file called /opt/usr/nx-on-wake/on-wake. To be clear,
         I am talking about a file called on-wake that is placed in a folder
         called /opt/usr/nx-on-wake. Why /opt/usr? Because that is the 
         partition with the largest free space on the NX cameras, and thus
         it will have the least impact on camera operation.
   If none of the above two files are present, the mod will do NOTHING.

   NB. Without any "on-wake" program, either on camera or on SD card, the
       camera will behave EXACTLY as in its original state. There is no
       way to prove it is modded unless the firmware is analysed by someone
       who knows his way around Linux/Tizen AND knows what to look for.
       A Samsung developer would be able to check, a service engineer most
       definitely not unless given step by step instructions by Samsung.
   
   This master mod is one-time for two reasons:
     1. it is dangerous UNLESS you follow the instructions TO THE LETTER
     2. there is no need to install it every time you install new mods or
        upgrades to already installed "satellite" mods.
   
   It also ensures that you have a back-out procedure in case a camera-resident
   mod misbehaves: you can always override satellite camera-resident mods by a
   simple file stored on the SD card.
   
   This mod comes with a very simple "blink three times" SD-card satellite mod
   that serves as demo AND can be used to disable any camera-resident
   misbehaving mods. After mod installation, the SD led will blink three times
   every time the camera is started. To remove the demo satellite mod, you
   should simply erase the nx-on-wake folder on the SD card. NB. The main mod
   will remain installed, it will just not do anything.
   
              COMPATIBILITY WITH PREVIOUS GENERATION MODS

   This is PARTIALLY compatible with any bluetooth-mods in the sense that a
   camera modded with this master mod can still run old-style mods as long as
   no NEW "satellite" mods are installed, with ONE exception: old-style bitrate
   mods will NOT work because this mod unavoidably changes camera memory
   configuration in an unpredictable way (reason: Linux Address Space Layout
   Randomisation - google it) rendering useless all mods that rely on fixed
   shared library memory addresses.
   NB. I do not recommend UNinstalling this master mod because without any
   satellites it has NO impact on camera operation - you can safely ignore its
   existence. However, if you insist on uninstalling it, see below.
   
   Please note that installing both types of mods (legacy and new "satellite")
   is likely to cause problems: they will compete for the key combinations and
   results will be unpredictable. So just don't. Use one or the other.

                        FOR THE DEVELOPERS

   The recommended way to check that your "satellite" mods can be installed is
   to test for the existence of /opt/usr/nx-on-wake folder.

                              HOW TO

     Turn OFF your brain. Do not do ANYTHING on your own initiative from now on
     until you see the SD card led blink three times.  Do not touch the camera,
     the screen or any camera button UNLESS instructed to do so.
              Otherwise you risk bricking your camera.

                       YOU HAVE BEEN WARNED.

  0. The zip file containing this README.txt includes everything you need.
  1. Check that: 
       - NX camera is on firmware v1.41 (NX1) or v1.12 (NX500).
       - battery is FULLY charged and that the camera is NOT connected to
         anything: Bluetooth, any cables (EVEN CHARGING), external flash,
         battery grip. EVERYTHING that can be disconnected should be
         disconnected except the battery, SD card and the lens.
       - power save settings are: Auto Display Off = off and 
                                  Power Save = 30 min.
       - camera is off
  2. To install the mod you will require a 6-digit number that you will need
     to assemble from pieces spread around this README. This is intentional.
     Why? because it will (hopefully) ensure that you thoroughly read these
     instructions. By the way, the middle two digits of the magic number are
     76. Write them down.
  3. Unzip the file where you found this README in the root of your SD card.
     Double-check that your SD card now contains two folders: install and 
     nx-on-wake, placed in the root of the card.
  6. Insert the SD card into your camera and power up the camera.
  7. Enter the installation code (magic number) when prompted.
  8.                   WAIT AT LEAST FIVE minutes
  9. Pull the battery and WAIT 10 SECONDS, then put the battery back in.
 10.                   WAIT AT LEAST FOUR minutes
 11. The last two digits you are looking for are six and nine.
 12. Turn off the camera using the power switch. NB the second digit you want
     is five. 
 13. Pull the battery, wait 5 seconds, put it back in and turn on the camera.
 14. Look at the SD card led: you will see it blink three times. 
     This is your proof that everything  went OK.
 15. You can now revert to the power saving settings you prefer.
 16. Uninstallation: I could have provided an uninstall script but there's
     no way to automatically return the camera to its ORIGINAL state (the
     hibernation image can be regenerated but it will NOT be the same and this
     is, as you saw, a dangerous process. SO, if you want to uninstall this
     mod, simply re-flash an official firmware. And finally, the first digit
     you want can be calculated by subtracting 32 from 35.

  As I wrote above, this is a one-time operation, further "satellite" mods are
  both EASY and SAFE to install since they will never touch any key part of the
  camera.

  A final word:
   If you find this program useful, I have a lens fund that only reached about
   half of its target :-) - your help would be much appreciated.

   goo.gl/7I67Rq      paypal: ppnx.vasile@dfgh.net
