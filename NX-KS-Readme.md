How to install:

		  1) start with a clean memory card (no files), turn on your Bluetooth
		  2) unzip the contents of the zip into the root of the sdcard
		  3) put the card in the camera, and re/start the camera
		  4) have some patience (there can be 1 or 2 auto-reboots)
		  5) when BG-mod is complete there will be [ Installation Complete ] message, followed by reboot
		  6) after boot, you will see [ Mod V1.xx ] (if you don't see it in 15 seconds, turn on the Bluetooth)
		  x) to uninstall the BT-mod - select: main menu > settings> Uninstall Mod



Details on the installation process:

Make sure you have turned on your Bluetooth before installing. After inserting the sdcard with the unplacked files from the zip, and starting the camera, initially we start in "factory mode", the script checks for BT-patch, and if one is detected it will be unintalled automatically. Follows automatic restart,  after which the BT-mod is installed automatically (making sure it is the proper version). Another reboot follows. After the Mod script gets loaded, and bitrates get customized, you will see a message similar to " [ Mod V1.xx ] ". If you don't see this message, the script did not start, and your Blutooth is probably "off". Turn it "on", and the script will start (you don't need to turn on BT each time the camera starts). If you need to use Bluetooth, you can start it from the "settings" menu.

.############

Key-combinations EV+:

		  AEL: immediate hibernation
		  UP: load UP profile
		  DOWN: load DOWN profile
		  Half-Press-Shutter: focus pull
		  mobile: telnet
		  EV (double-click EV): Main Menu  (NX500)
		  OK: Main Menu (NX1)

.#############

Main Menu
- Video Birtates
- Custom Functions
- Profiles
- Settings
- Hibernate
- Sleep

Video Bitrates
 - lists all set bitrates
 - allows for changing them persistently (that means settings are kept even after camera restart)
 - Note: Setting "Current" bitrate will only temporary change the bitrate of the profile (resolution/quality) you have had selected at the moment, and it will be cleared on camera restart.

Custom Functions
- Focus Stacking
- Focus Buttons
- Batch Recording (continuous recording)
- LCD-off Recording
- Kill switch (removes keyscan and gui from memory)

Profiles
- save/load UP or DOWN profile
- save/load FullBackup (all camera settings)

Settings
- Silent Shutter (nx500 only)
- VGA to 2.5K (nx500 only)
- No Rec Limit
- Refocus on Boot (on hibernate camera remembers last focus distance, and will auto-refocus if option is selected)
- Uninstall Mod

.#############


Focus buttons 
		
		Program that displays series of buttons on top of the screen
		long press (1+s) to save current focus position
		click to restore saved focus position
		Can be used for studio shooting, astrophotography 
		(focus on infinity during day, recall the focus during the night), etc.

.#############

Focus stacking

	Focus on near point - press "Near"
	Focus on far point - press "Far"
	Click "Stack" and wait for it to finish
	Files are in the usual place - remember to fix exposure/awb/etc as you normally would

.#############

Focus pull - EV+half-press shutter button

	Focus on subject 1
	press EV+half-press shutter button
	Focus on subject 2
	consecutive EV+half-press shutter button will be switching between focus of the two subjects.
	
.#############

Refocus on Boot

	When using hibernation (EV+AEL) the camera records last focus distance
	If this option is enabled, camera will refocus to that focus distance on boot
	
.#############

Batch recording

	The main target users are NX500, who even with "removed timelimit" still have restrictions for 4K and UHD
	When button is pressed, the camera starts recording and auto-starts new clips until "Rec" is pressed.
	
.#############

Kill switch
	
	Stops and removes the program "keyscan" ( which monitors your key-press combinations EV+* )
	If you will have an option to let it autorestart in 3 minutes.
	Until "keyscan" restart, you will have no way of starting the menu, or use key-combinations.
	Bitrate modifications remain, but if not restarted in 3 minutes, you will need camera restart to enable menus.
.#############

Thanks to Otto for the programs that make this possible - keyscan, gui, poker, focus stacking, focus buttons, .. to name a few
Thanks to Vasile for coming up with the values for the bitrate-change and nx500's 2.5K mod 
(the values used here are based on his calculations)
