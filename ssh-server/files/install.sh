#!/bin/bash
#
if [ ! -f /mnt/mmc/authorized_keys ]; then
	/opt/usr/nx-ks/popup_timeout "No authorized_keys file, aborting."  10 &
	exit 1
fi

if [ -x /opt/usr/nx-ks/init.sh ]; then
	/opt/usr/nx-ks/popup_timeout "Installing SSH server..."  3 &
	mkdir -p /opt/ssh/
	cp -ar /mnt/mmc/ssh/* /opt/ssh/
	mkdir -p /opt/home/root/.ssh/
	cp -ar /mnt/mmc/authorized_keys /opt/home/root/.ssh/
	chmod -R go-rwx /opt/home/root/.ssh/
	grep dropbear /opt/usr/nx-ks/init.sh || {
		cp /opt/usr/nx-ks/init.sh /opt/usr/nx-ks/init.sh.bak
		cat >> /opt/usr/nx-ks/init.sh <<EOF
# start dropbear; -R = create host-keys as required
# DANGER ZONE: add -B to allow passwordless root logins
/opt/ssh/dropbear -R &
EOF
		/opt/ssh/dropbear -R &
	}
	rm -r /mnt/mmc/ssh/ /mnt/mmc/install.sh /mnt/mmc/nx_cs.adj /mnt/mmc/info.tg /mnt/mmc/authorized_keys
        sync;sync;sync
	sleep 2
	killall popup_timeout
	/opt/usr/nx-ks/popup_timeout "SSH installation complete."  3
	reboot
fi
