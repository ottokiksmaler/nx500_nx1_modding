#!/bin/bash
#
# Copyright (C) 2016  Vasile Dumitrescu, (ppnx.vasile@dfgh.net)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
# 

killall dfmsd

  # ========= force LCD on (crash on EVF) =========
st app disp lcd
sleep 1

# ========= only run on suitable firmware =========
if [ `/opt/storage/sdcard/install/nx-model` != nx500 ] &&
   [ `/opt/storage/sdcard/install/nx-model` != nx1 ]; then
  /opt/storage/sdcard/install/popup_ok "Camera or firmware not supported.\n\nPress OK to exit"
  exit
fi

res=$(/opt/storage/sdcard/install/popup_entry "Magic number from README?" Confirm Cancel 0 number)
if [ $res -eq 357669 ]; then
  cp -f /opt/storage/sdcard/install/popup_timeout /tmp
  /tmp/popup_timeout "Thanks. Preparing the ground." 4 &
    # unlock camera root filesystem so we can copy stuff in there
  mount -o remount,rw /
    # copy the nx-on-wake binary to the camera
  cp -f /opt/storage/sdcard/install/nx-on-wake /usr/local/bin/
    # copy service definition to "local" services location
  cp -f /opt/storage/sdcard/install/nx-on-wake.service /etc/systemd/system/
  cd /etc/systemd/system/
    # enable the service so that next time the camera boots it will be activated
  /usr/bin/systemctl enable nx-on-wake.service
    # lock back camera root filesystem
  mount -o remount,ro /
    # prepare the "satellite" mod storage folder
  mkdir -p /opt/usr/nx-on-wake
    # make sure the filesystem is consistent on flash
  sync;sync;sync
  sleep 1
  sync;sync;sync
  sleep 1
  sync;sync;sync
  sleep 2
  /tmp/popup_timeout "Done. Please wait 5 minutes." 4 &
    # clean up
  rm -Rf /opt/storage/sdcard/install
  rm -f  /opt/storage/sdcard/info.tg
  rm -f  /opt/storage/sdcard/README.txt
  rm -f  /opt/storage/sdcard/COPYING
  sync;sync;sync
  sleep 1
  sync;sync;sync
  sleep 1
    # now for the dangerous part
  /usr/bin/systemctl rescue
else
  /opt/storage/sdcard/install/popup_timeout "Sorry. Please read the README.txt." 10 &
fi
