# Making Permanent Bitrate Mods

Permanent => stored to hibernation image => modifications are available instantly with no need to wait for mods to load.

# BEWARE - THIS MODIFIES YOUR CAMERA PERMANENTLY 
# BEWARE - do NOT attempt this unless you know what you are doing.
### TESTED ON NX500 FW 1.11

Also, read this first https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/doc/Update_hibernation_image.md

Modifying the **/usr/lib/libmmutil_movie.so.0.0.0** file on filesystem and then invoking **systemctl rescue**, restarting and powering off normally causes hibernation image to be updated with modified values from libmmutil_movie file (that is the file we are changing in memory when we are applying bitrate mods).

Positives: By doing this the bitrate modifications are **always** active - battery popping or not and there is no need re-apply them.
Negatives: You cannot easily change them this way - it involves a minute or so of procedure. You can still change them normally via mods.

TODO: Test modifications to di-camera-app in order to have persistent 2.5k video of decent bitrate in place of VGA.

This is a short transcript of what was done on camera:

```
[root@drime5 ~]# mount / -o remount,rw
[root@drime5 lib]# pmap -x 247|grep libmmutil_movie
b4046000       8       8       0 r-x--  libmmutil_movie.so.0.0.0
b4048000      28       0       0 -----  libmmutil_movie.so.0.0.0
b404f000       4       4       4 rw---  libmmutil_movie.so.0.0.0
[root@drime5 lib]# poker /usr/lib/libmmutil_movie.so.0.0.0 0x8f0:#16     
0x000008f0:49f24033c0f22110c0f23423022c08bf
[root@drime5 lib]# poker /usr/lib/libmmutil_movie.so.0.0.0 0x8f0:#4 
0x000008f0:49f24033
[root@drime5 lib]# poker /usr/lib/libmmutil_movie.so.0.0.0 0x8f0:48
[root@drime5 lib]# poker /usr/lib/libmmutil_movie.so.0.0.0 0x8f0:#4
0x000008f0:48f24033
[root@drime5 lib]# sync;sync;sync                                      
[root@drime5 lib]# systemctl rescue

Broadcast message from root@drime5 on pts/0 (Wed 2016-06-01 17:45:17 KST):

The system is going down to rescue mode NOW!

drime5 login: root
[root@drime5 ~]# ps aux|grep di-cam
root      246 26.6  5.2 270364 26828 ?        S<sl 17:48   0:16 /usr/apps/com.samsung.di-camera-app/bin/di-camera-app
root      463  0.0  0.1   2184   604 pts/0    S+   17:49   0:00 grep di-cam
[root@drime5 ~]# pmap -x 246|grep libmmutil_movie
b40f8000       8       8       0 r-x--  libmmutil_movie.so.0.0.0
b40fa000      28       0       0 -----  libmmutil_movie.so.0.0.0
b4101000       4       4       4 rw---  libmmutil_movie.so.0.0.0
[root@drime5 ~]# mount / -o remount,rw
[root@drime5 ~]# poker /usr/lib/libmmutil_movie.so.0.0.0 0x8f0:#4
0x000008f0:48f24033
[root@drime5 ~]# poker 246 0x0b40f88f0:#4                        
0xb40f88f0:48f24033
```
