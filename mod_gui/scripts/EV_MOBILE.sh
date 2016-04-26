DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
killall telnetd
$DIR/telnetd &
IP=`ip addr ls|grep inet|grep mlan0|cut -d/ -f 1`
$DIR/popup_timeout "Telnet: $IP" 10
 
