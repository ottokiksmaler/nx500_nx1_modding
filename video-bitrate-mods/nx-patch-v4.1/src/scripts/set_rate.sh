#!/bin/bash
# usage: set_rate.sh currentRate camera slot
rate=$(/opt/usr/scripts/popup_entry "Please enter bit rate:" "Set bit rate" Cancel $1 number )
if [[ $rate -gt 0 ]]; then 
  /bin/sed -i -r -e "s/$2:$3:[^ ]+/$2:$3:$rate/" /tmp/initial_patches.sh
  /opt/usr/scripts/apply.sh
fi
