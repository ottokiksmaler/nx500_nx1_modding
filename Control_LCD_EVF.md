# Controlling LCD / EVF display

**This does not turn off the touchscreen - it still works**

You can control what is shown on what video display device by using **st app bb** command as follows:

st app bb [lcd|evf|tv][on|off|osd|video]

First parameter is lcd, evf or tv and has obvious meaning. I have tested only back LCD as I have NX500 (so no EVF).

Second parameter can be:
  1. on - show everything
  2. off - show nothing (powers down the display - could be useful for long exposures, timelapses, etc)
  3. video - show just live video without any of the overlay data 
  4. osd - show only the overlay data - no live video (also saves power due to AMOLED nature of the display)

This command can be used to control the displays during any operation including video.

Selecting display can be mapped to EV+key combination in order to solve apparent issue with NX1 and non-selectable display after video capture starts.
