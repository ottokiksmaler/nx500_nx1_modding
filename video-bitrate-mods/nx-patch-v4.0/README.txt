                  Samsung NX1 and NX500 nx-patch

                               v4.1

     Copyright (C) 2016  Vasile Dumitrescu, (ppnx.vasile@dfgh.net)

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

Version 4.1
  - added automatic installer

Version 4.0:
  - supports (only) NX500 v1.12 and NX1 v1.41
  - renamed to nx-patch as it is intended to contain more than just bitrate
    adjustments :-) (watch this space)
  - removed NX500 15 min UHD and 25 min FHD/50 and FHD/60 limits
  - enabled permanent DEV menu access without a "special" SD card file
      NB you still need to do the key dance to activate it
  - enabled (many) more video slots - see enclosed nx-patch.png
  - self-contained - does not rely on any additional scripts or on bash
		to identify camera model and version which should improve camera 
		stability through (much) lower memory requirements
  - improved safety and flexibility: only applies patches that are compatible
    with camera model on which it runs.
  - eliminated gdb :-) - program is now only 26kB
  - no longer needs a computer science degree to use it :-) uses 
    human-readable arguments :-)
  - behind the scene:
    + prepared for the future: I am now working on hibernation image
      integration (to dispose of BT and have instant-on patching) and since
      that WILL change memory addresses the patcher is now independent of
      memory address (i.e. it will support both original firmware and
      re-hibernated versions, as long as they report the same Samsung
      firmware version)
    + flexible architecture for instant integration of future patches

Version 3.0:
  - added 2.5k resolution

Version 2.0:
  - added support for more bit rate slots and for NX500

Initial version: v1.0
  - replaces NX1 80 Mbps video bit rate 

    
                              How To

  0. Make sure your NX camera is on firmware v1.41 (NX1) or v1.12 (NX500)
  1. Make sure that Otto's SD card bluetooth execute method is ENABLED.
       => look for Running_scripts_without_factory_mode_BT.md on
          https://github.com/ottokiksmaler/nx500_nx1_modding/

     The package containing the file you are reading now also includes
     a zipfile that implements Otto's mod in a relatively easy to use manner.
        Zip file name: nx-bt-run-v1.zip, unzip it on your computer and read
        its README.txt.

     Alternatively, use any method available to you to run this program on
     your camera.

  2. Usage: nx-patch camera:from:to [...]

     Multiple argument triplets are supported as long as they are separated by
     white space (spaces, etc.).

       camera = one of nx1, nx500

       from   = one of pro1, pro2, pro3
                       hq1, hq2, hq3, hq4, hq5, hq6, hq7, hq8
                       nq5, nq6, nq7, nq8, other
                       DC, UHD, FHD, HD, VGA, 2k5

     Please refer to the enclosed .png picture for an illustration of what each
     bitrate and resolution slot corresponds to.

     NB I created myself the <other> slot for the extra 2k5 video resolution
        that is enabled by sys_param movie size 2560_1440_30p [see github]

       to     = a bitrate, expressed in Mbps, e.g. 123 for 123,000,000 bps, or
                a target resolution: toDC, toUHD, toFHD, toHD, toVGA, to2k5

                NB you are no longer limited to a list of predefined bit rates,
                you can pick any rate you want

     Arguments are case-insensitive - you can use Uhd, UHd, uHD, UHD etc.

     The program is safe to run on any of the supported cameras and it will
     intelligently apply only what makes sense. For example:
          ./nx-patch nx500:DC:to2k5 will work on nx500 but will not change nx1
          ./nx-patch nx1:vga:121 will set nx1's vga bitrate to 121Mbps
          ./nx-patch nx500:hd:78 will do nothing since you mixed
                     resolution with a bitrate
          ./nx-patch nx500:HD:toVGA nx1:DC:toUHD nx1:pro2:150 will detect
                     the camera on which it runs and
                     will only apply matching patches

  A final word:
   If you find this program useful, I have a lens fund that only reached about
   half of its target :-) - your help would be much appreciated.

   goo.gl/7I67Rq      paypal: ppnx.vasile@dfgh.net
