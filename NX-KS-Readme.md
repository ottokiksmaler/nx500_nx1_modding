NX-KS Mod-pack

How to install:

      1) start with a clean memory card (no files), turn-on your Bluetooth
      2) unzip the contents of the zip into the root of the sdcard
      3) put the card in the camera, and start the camera
      4) have some patience (there can be 1 or 2 auto-reboots)
      5) when BT-Mod is complete there will be [ Installation Complete ] message, followed by reboot
      6) after boot, you will see [ Mod V1.xx ] (if you don't see it in 15 seconds, turn on the Bluetooth)
      x) to uninstall select: main menu > settings> Uninstall Mod



Key-combinations EV+*:
      AEL: immediate hibernation
      UP: load UP profile
      DOWN: load DN profile
      Half-Press-Shutter: focus pull
      mobile: telnet
      EV (double-click EV): Main Menu  (NX500)
      OK: Main Menu (NX1)



Main Menu

	Video Birtates    	Custom Functions
	Profiles    		Settings
	Hibernate	    	Sleep




Video Bitrates

	Bitrates are grouped by resolution group / quality. Note that for NX1 high-fps bitrates will be as the ones set for 4K/UHD. 
	Changing bitrates for a given group is persistent (it will survive reboot). Changing “current” bitrate changes only temporary the current settings for the resolution/quality, which is selected at the moment, and it will be lost on reboot.
Accepted bitrate values are in essence from 40Mbps to 320Mbps in 10Mbps increments.

Complete list: 
35,40,45,50,55,60,65,70,75,80,85,90,95,
100,110,120,130,140,150,160,170,180,190,
200,210,220,230,240,250,260,270,280,290,
300,310,320




	Custom Functions

	Focus Stacking    	Focus Buttons
	Batch Recording 	LCD-off Recording
	Mod v1.**  (about)	Kill Switch (turns off Mod software, custom bitrates remain)


	
	Profiles
	
	save/load UP or DN profile
	save/load FullBackup (all camera settings)
	Saved profiles are stored in /sdcard/presets/ and you can copy and backup them as needed.



	Settings

	Silent Shutter (nx500 only)		VGA to 2.5K (nx500 only)
	No Rec Limit (on nx500 4K/UHD limits remain, NX1 has problems with too long files)
	Refocus on Boot (return to last focus after hibernation)
	Enable Bluetooth (use this to enable Bluetooth functionality while the mod is installed)
	Uninstall Mod




	Added Functionality 

Focus buttons

	Program that displays series of buttons on top of the screen
	long press (1+s) to save current focus position
	click to restore saved focus position
	Can be used for studio shooting, astrophotography 
	(focus on infinity during day, recall the focus during the night), etc.

Focus stacking

	Focus on near point - press "Near"
	Focus on far point - press "Far"
	Click "Stack" and wait for it to finish
	Files are in the usual place - remember to fix exposure/awb/etc as you normally would

Focus pull (EV+half-press shutter button)

	Focus on subject 1
	press EV+half-press shutter button
	Focus on subject 2
	Consecutive EV+half-press shutter button will be switching between focus of the two subjects.
	Adjusting focus is possible is possible at any time.



Refocus on Boot

	When using hibernation (EV+AEL or Menu>Hibernate) the camera records last focus distance
	If this option is enabled, camera will refocus to that focus distance on boot


Batch recording

	The main target users are NX500, who even with "removed time-limit" still have restrictions for 4K and UHD. NX1 also has some problems with recording too long. When button is pressed, the camera starts recording and auto-starts new clips until "Rec" is pressed. Clips are split in 840sec batches, and will have about a second gap in the continuity. 


Kill Switch

	Stops and removes the program "keyscan" from memory ( which monitors your key-press combinations EV+*, so there will be no key-combinations and no menu to access )
You have an option to let it auto-restart in 3 minutes.
Bitrate modifications remain. If not restarted in 3 minutes, you will need camera-restart to enable menus.



Thanks to Otto for the programs that make this possible - keyscan, gui, poker, focus stacking, focus buttons, ... to name a few.

Thanks to Vasile for coming up with the values for the bitrate-change and nx500's 2.5K mod (the values used here are based on his calculations) 

Thanks to the bad weather recently, which helped by keeping me in front the computers. You can get in touch with me on www.fb.com/KinoSeed/ 


Donations

Otto: 

Q: So, where's the Donate button? A: Nowhere. Find a suitable charity and donate. If you cannot afford it, find a local charity and see if they need help in person - it will do you a world of good. 

Vasile: 
https://docs.google.com/spreadsheets/u/1/d/1azq3GqVkI3uimTLABokyHcoTACackLvKDu5TcGo_Gsg/pubhtml

Kino:

I have to go with Otto on this one. Pay it forward.
… although producers (especially ones based outside EU) interested in access to market for option-deals for literary materials, are quite welcome as donations. ; )

LINKS 

The hub for all information: https://github.com/ottokiksmaler/nx500_nx1_modding
Latest version: https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/NX-KS.zip
