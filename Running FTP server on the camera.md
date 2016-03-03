#Running FTP server on the camera.md

You have to cross compile **busybox** for your camera or use the one present in NX300 open source package like described in [telnet server instructions](https://github.com/ottokiksmaler/nx500/blob/master/Running-telnet-server-on-camera.md).

Since **busybox** is multi-tool you need it to be either copied or linked to as **tcpsvd** and **ftpd**.

One place where you can put it to remain on camera is to create the /opt/usr/devel/bin directory (it's in PATH) and put binaries there as it makes life much easier.

To run it either use inetd or simply run:
```
[root@drime5 ~]# tcpsvd -u root -vE 0.0.0.0 21 ftpd -w -v /opt/storage/sdcard &
tcpsvd: listening on 0.0.0.0:21, starting, uid 0, gid 0
tcpsvd: start 451 192.168.43.46:21-192.168.43.85:42309
tcpsvd: status 1/30
...
```
This tells it to be verbose and use stderr for logging as well as enabling uploads (-w). For "production" use log to syslog.
