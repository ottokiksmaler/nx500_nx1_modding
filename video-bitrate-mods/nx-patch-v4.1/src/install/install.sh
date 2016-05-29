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

# ========= force LCD on (crash on EVF) =========
st app disp lcd
sleep 1

# ========= only run on suitable firmware =========
if [ $(/mnt/mmc/install/nx-model) != "nx500" ] &&
   [ $(/mnt/mmc/install/nx-model) != "nx1" ]; then
  /mnt/mmc/install/popup_ok "Camera or firmware not supported.\n\nPress OK to exit"
  exit
fi

# ========= clean if necessary =========
if [ -x /usr/sbin/bluetoothd.orig ]; then
  /mnt/mmc/install/popup_timeout "Cleaning existing mod" 3 &
  killall -q keyscan
  killall -q mod_gui
  rm /tmp/keyscan.pid
  rm -r /opt/home/scripts/
  swapoff /opt/usr/home/swapmod
  rm /opt/usr/home/swapmod
  mount -o remount,rw /
  rm /usr/sbin/bluetoothd
  mv /usr/sbin/bluetoothd.orig /usr/sbin/bluetoothd
  chmod +x /usr/sbin/bluetoothd
  mount -o remount,ro /
fi
sleep 4

# ========= and now install =========
# using /opt/usr because it is the largest mostly empty partition
/mnt/mmc/install/popup_timeout "Please wait, installing" 3 &

# ========= mod launch based on bluetooth ===============
# =======================================================
# =======================================================
# thanks to ottokiksmaler@github for the bluetooth method
# =======================================================
# =======================================================
mount -o remount,rw /
mv /usr/sbin/bluetoothd /usr/sbin/bluetoothd.orig
cat >/usr/sbin/bluetoothd << EOF
#!/bin/bash
if [ -x /opt/usr/scripts/init.sh ]; then
  /opt/usr/scripts/init.sh &
fi
/usr/sbin/bluetoothd.orig -d &
EOF
chmod +x /usr/sbin/bluetoothd
mount -o remount,ro /

# ========= install mod in folder =========
mkdir -p /opt/usr/scripts
cp -r /sdcard/scripts/* /opt/usr/scripts/
chmod +x /opt/usr/scripts/*.sh
chmod +x /opt/usr/scripts/popup_*
chmod +x /opt/usr/scripts/telnetd
chmod +x /opt/usr/scripts/keyscan
chmod +x /opt/usr/scripts/mod_gui
chmod +x /opt/usr/scripts/nx-patch

# ========= clean up =========
rm /sdcard/info.tg
rm /sdcard/README.txt
rm /sdcard/nx-patch.png
rm /sdcard/COPYING
rm -rf /sdcard/scripts
sleep 4
/mnt/mmc/install/popup_timeout "All done. Rebooting..." 3 &
rm -rf /sdcard/install
sync;sync;sync
sleep 4
killall dfmsd
reboot
