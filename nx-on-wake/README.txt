                  Samsung NX1 and NX500 nx-on-wake

                               v1.0

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

Version 1.0 - 2016-06-12
  - initial version
  
                          DESCRIPTION
                          
   This is a one-time MASTER mod, which will free you from depending on
   bluetooth for any "satellite" NX camera mods built to take advantage of it.
   
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

   This is completely compatible with any bluetooth-mods in the sense that a
   camera modded with this master mod can still run old-style mods as long as
   no NEW "satellite" mods are installed. NB. I do not recommend UNinstalling
   this master mod because without any satellites it has NO impact on camera
   operation - you can safely ignore its existence. However, if you insist on
   uninstalling it, see below.
   
   Please note that installing both types of mods (legacy and new "satellite")
   is likely to cause problems: they will compete for the key combinations and
   results will be unpredictable. So just don't. Use one or the other.

                        FOR THE DEVELOPERS

   The recommended way to check that your "satellite" mods can be installed is
   to test for the existence of /opt/usr/nx-on-wake folder.

                              HOW TO

  0. The zip file containing this README.txt includes everything you need.
  1. Make sure your NX camera is on firmware v1.41 (NX1) or v1.12 (NX500).
  2. Make sure your battery is FULLY charged and that the camera is NOT
     connected to anything: Bluetooth, any cables (EVEN CHARGING), external
     flash, battery grip. EVERYTHING that can be disconnected should be
     disconnected except the battery, SD card and lens.
  3. To install the mod you will require a 6-digit number that you will need
     to assemble from pieces spread around this README. This is intentional.
     Why? because it will (hopefully) ensure that you thoroughly read these
     instructions: if you do not follow them to the letter you WILL brick
     your camera. YOU HAVE BEEN WARNED. By the way, the middle two digits
     of the magic number are 76. Write them down.
  4. Unzip the file where you found this README in the root of your SD card.
     Double-check that your SD card now contains two folders: install and 
     nx-on-wake, placed in the root of the card.
  5. Insert the SD card into your camera and power it up.
     NB. I mean power up the camera, not the SD card :-)
  6. You will be presented with a prompt to enter the installation code.
     Unless you enter it exactly the installation will abort.
  7. Make sure you have a watch with a seconds indicator.
  8. Take a piece of paper and write down the exact time - to the second!
     Be aware that this is an essential step. By the way, the last two digits
     you are looking for are six and nine.
  9. After you marked down the time, enter the magic number as prompted.
 10. The camera screen will freeze. DO NOT TOUCH the camera. Do not even
     BREATHE on it. On NX1 the camera might seem to have rebooted in "normal"
     mode. DO NOT BE FOOLED. WAIT.
 11. Now wait 5 minutes (in reality two minutes are more than enough but
     this is so serious that I insist on taking five - I MAY have bricked my
     camera because I did not wait enough, and you MIGHT too if you are 
     impatient).
 12. Read point 11 again - you have plenty of time. It is a key point.
 13. Go get a coffee. Read a book. Whatever, as long as you DO NOT TOUCH
     the camera for five minutes. Refer to the time you wrote on paper and 
     make sure AT LEAST five minutes have elapsed since. 
 14. Now pull the battery WITHOUT touching any button (not even the power
     switch - leave it on). Just open the battery compartment and
     pull the battery.
 15. Wait 10 seconds. I repeat: wait 10 seconds. Don't say I did not tell
     you to wait. Do not touch the camera for these 10 seconds.
 16. Put back the battery in the camera. Do not touch any button, not even the
     power switch (it should already be ON). The camera should start and the SD
     card led should start flashing slowly. At some point the LED will turn
     off, and after some more time you might hear the shutter (I think) and
     after a bit more time the camera should be powered up as usual. The entire
     process between putting the battery back in and the finalisation of the
     process is 4 minutes or less. Please BE PATIENT and DO NOT TOUCH (by the
     way, the second digit you want is five) the camera during this time.
 17. Did you wait four minutes? Sure? Do you prefer bricking the camera to
     waiting four minutes? Do you see the camera user interface?
     Then turn off the camera. Pull again the battery. Wait 5 seconds.
     Plug in the battery. Turn on the camera. Look at the SD card led: 
     you will see it blink three times. This is your proof that everything
     is OK. You are done now. You can drink that coffee and start installing
     other mods that depend on this one.
 18. Uninstallation: I could have provided an unistallation script but there's
     no way to automatically return the camera to its ORIGINAL state (the
     hibernation image can be regenerated but it will NOT be the same and this
     is, as you saw, a dangerous process. SO, if you want to uninstall this
     mod, simply re-flash an official firmware. And finally, the first digit
     you want can be calculated by subtracting 32 from 35.

  NB you can breathe now: you will NEVER have to do it again, further "satellite"
  mods are both EASY and SAFE to install, and if worst comes to worst, you can
  also disable them easily.

  A final word:
   If you find this program useful, I have a lens fund that only reached about
   half of its target :-) - your help would be much appreciated.

   goo.gl/7I67Rq      paypal: ppnx.vasile@dfgh.net
