#!/bin/bash
cp /mnt/mmc/scripts/install/info_factory.tg /mnt/mmc/info.tg
sync;sync;sync
/mnt/mmc/scripts/popup_ok "Install complete - Reboot?" && reboot
