#!/bin/bash
BTD="/usr/sbin/bluetoothd"
BTD="./bluetoothd"
BTDO="${BTD}.orig"

mount -o remount,rw /
if [ ! -x $BTDO ]; then
	echo "Creating backup $BTDO of $BTD file"
	cp $BTD /mnt/mmc/scripts/bluetoothd.orig
	mv $BTD $BTDO
fi
cat >$BTD << EOF
#!/bin/bash
if [ -x /mnt/mmc/scripts/init.sh ];
then
  killall keyscan
  rm -f /tmp/keyscan.pid
  /mnt/mmc/scripts/init.sh &
elif [ -x /opt/usr/devel/scripts/init.sh ];
then 
    /opt/usr/devel/bin/init.sh &
fi
$BTDO -d &
EOF
chmod +x $BTD
sync;sync;sync
mount -o remount,ro /
mv /mnt/mmc/info.tg /mnt/mmc/info-installed.tg
sync;sync;sync




