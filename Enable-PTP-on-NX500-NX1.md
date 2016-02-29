#Enabling support for PTP over USB for NX500 and related cameras (NX2000 and newer)

**This is a very simple non-destructiv "hack" that you can safely try.**

To best of my knowledge NX500 is not supposed to be used tethered by USB to PC, that was left as a domain of NX1 as professional model. When you connect it via USB cable to PC it automatically switches SD card to mass storage mode and disables any camera operation (at least my NX500 does when connected to Linux).

What follows is a very simple "hack" (it's not really a hack) that enables the use of camera via PTP/MTP protocol - enabling use of camera while still having access to all image files (and possibly remote control, see later) in real time.

First of all thanks to tecnoworld for providing old versions of firmware that proved easier to work with when compared to current versions.

Second thanks goes to Samsung engineers that made many nice things in firmware I'm trying to access. You guys rock. Your management guys - not so much.

To use NX500 and related cameras in PTP/MTP mode:

1. Create text file with just a line break (CR/LF - simple enter in Notepad will do) named info.tgw in the root of the SD card.

2. Insert SD card in camera

3. Connect camera via USB cable to PC

4. Turn on camera

That's it.

You should see a series of green dots on the left side of the camera indicating PTP mode is active.

info.tgw file instructs the camera to start the daemon process in background and wait for PTP/MTP commands from the computer.

Under Linux I can easily access the DCIM folder with any file browser and see how the files are being written to the card in real time (I use a slow class 4 card and shot RAW files - you can see the size increasing). This enables one to automatically copy files off camera (at ~18MB/s for this card) to PC for further editing. Only difference I found was that photo size was grayed out in the menu (it's 28MP) - JPG works, RAW, works, modes work, even video files (BTW, they are written down 4MB at a time - nice for streaming offload to PC).

Unfortunately, I can't trigger shooting or any other setting from command line (neither gphoto nor libptp support Samsung).

Here is output of gphoto:

gphoto2 --port usb: --abilities
Abilities for camera : USB PTP Class Camera
Serial port support : no
USB support : yes
Capture choices :
: Image
: Preview
Configuration support : yes
Delete selected files on camera : yes
Delete all files on camera : no
File preview (thumbnail) support : yes
File upload support : yes

From what I have seen so far on camera - dfmsd daemon expects textual commands from the computer. This should be doable with libptp.
