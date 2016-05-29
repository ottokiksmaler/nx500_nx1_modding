#!/bin/bash

# rebuild menus to reflect current state
/bin/awk 'BEGIN { FS="[: ]" }; /nx500:[DUFHV].+/ { print "button|" $2 " ( now: " substr($3, 3) " )|/opt/usr/scripts/mod_gui /opt/usr/scripts/chg_res_" tolower($2) "\nbutton|-|" }' /tmp/initial_patches.sh >/tmp/resolutions.NX500
/bin/awk 'BEGIN { FS="[: ]" }; /nx1:[DUFHV].+/   { print "button|" $2 " ( now: " substr($3, 3) " )|/opt/usr/scripts/mod_gui /opt/usr/scripts/chg_res_" tolower($2) "\nbutton|-|" }' /tmp/initial_patches.sh >/tmp/resolutions.NX1
/bin/awk 'BEGIN { FS="[: ]" }; /nx500:[phn].+/   { print "button|" $2 " ( now: " $3 " )|/opt/usr/scripts/set_rate.sh " $3 " nx500 " $2  }' /tmp/initial_patches.sh >/tmp/bitrates.NX500
/bin/awk 'BEGIN { FS="[: ]" }; /nx1:[phn].+/     { print "button|" $2 " ( now: " $3 " )|/opt/usr/scripts/set_rate.sh " $3 " nx1   " $2  }' /tmp/initial_patches.sh >/tmp/bitrates.NX1
echo "button| |/bin/true" >>/tmp/bitrates.NX1

# run the patcher
. /tmp/initial_patches.sh
# free memory to the max
echo 3 > /proc/sys/vm/drop_caches
