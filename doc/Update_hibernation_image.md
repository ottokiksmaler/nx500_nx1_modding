#Update hibernation image

This is the image that is unpacked to RAM when you power on the camera.

#Any changes to  the state of the camera at the moment of power-off after ```systemctl rescue``` and cold-booting are *PERMANENT*!

**If you want to play around but *not save permanently* anything - don't power the camera off - pop the battery out**

**TLDR** - new persistent PID of di-camera-app is 248, keyscan also survives hibernation (works without bluetooth now) - we have a stable way to hack suspended image that is run on powering on the camera. :)

  1. **Note:** when you do ```systemctl rescue``` wait a bit (a minute? have no idea, maybe no need for the wait) and then pop-out the battery and reinsert it (power switch does nothing). 
  2. **DON'T PANIC** It will boot **slowly**
  3. Do whatever you want to camera tunning state (apply bitrate mods, start applications, whatever) and power-off the camera nicely **to preserve current state**
  4. If you **don't** want to preserve it **pop the battery out**
  5. If you still panic, don't - firmware flashing still works :)

###HOWTO:
```
[root@drime5 system]£ systemctl rescue  

Broadcast message from root@drime5 on pts/0 (Thu 2016-05-12 09:33:46 KST):

The system is going down to rescue mode NOW!

[root@drime5 system]£ 
telnet> Connection closed.
telnet 192.168.43.90
Trying 192.168.43.90...
Connected to 192.168.43.90.
Escape character is '^]'.


*                 SAMSUNG LINUX PLATFORM                   *


drime5 login: root
[root@drime5 ~]£ ps aux|grep di-camera
root      248 27.5  5.1 269728 26280 ?        S<sl 09:39   0:22 /usr/apps/com.samsung.di-camera-app/bin/di-camera-app
root      465  0.0  0.1   2184   612 pts/0    S+   09:41   0:00 grep di-camera
```
Also to check if everything is in the same place in memory:
```
[root@drime5 ~]£ cat /proc/248/maps 
00008000-00440000 r-xp 00000000 b3:0a 14606      /usr/apps/com.samsung.di-camera-app/bin/di-camera-app
00447000-0049d000 rw-p 00437000 b3:0a 14606      /usr/apps/com.samsung.di-camera-app/bin/di-camera-app
0049d000-00981000 rw-p 00000000 00:00 0          [heap]
6cf6f000-6cf70000 ---p 00000000 00:00 0 
6cf70000-6d76f000 rwxp 00000000 00:00 0 
6d76f000-6d8c1000 rw-p 00000000 00:00 0 
6d8c1000-6d8c2000 ---p 00000000 00:00 0 
6d8c2000-6e0c1000 rwxp 00000000 00:00 0          [stack:289]
6e106000-6e329000 rw-p 00000000 00:00 0 
6e329000-6e32a000 ---p 00000000 00:00 0 
6e32a000-6eb29000 rwxp 00000000 00:00 0          [stack:285]
6eb29000-6eb30000 r--s 00000000 b3:0a 3552       /usr/lib/gconv/gconv-modules.cache
6ebff000-6ed51000 rw-p 00000000 00:00 0 
6ed51000-6ef6c000 r--s 00000000 b3:0a 1550       /usr/share/elementary/themes/tizen-default.edj
6ef6c000-6f0be000 rw-p 00000000 00:00 0 
6f0be000-6f5be000 rw-s 84c00000 00:05 16         /dev/mem
6f5be000-6f5bf000 r-xp 00000000 b3:0a 11056      /usr/lib/evas/modules/loaders/eet/linux-gnueabi-armv7l-1.7.99/module.so
6f5bf000-6f5c6000 ---p 00001000 b3:0a 11056      /usr/lib/evas/modules/loaders/eet/linux-gnueabi-armv7l-1.7.99/module.so
6f5c6000-6f5c7000 rw-p 00000000 b3:0a 11056      /usr/lib/evas/modules/loaders/eet/linux-gnueabi-armv7l-1.7.99/module.so
6f5c7000-6f5c8000 ---p 00000000 00:00 0 
6f5c8000-6fdc7000 rwxp 00000000 00:00 0          [stack:281]
6fdc7000-6fdcf000 r-xp 00000000 b3:0a 77         /usr/lib/lib_DNSe_NRSS_ver225.so
6fdcf000-6fdd6000 ---p 00008000 b3:0a 77         /usr/lib/lib_DNSe_NRSS_ver225.so
6fdd6000-6fdd7000 rw-p 00007000 b3:0a 77         /usr/lib/lib_DNSe_NRSS_ver225.so
6fdd7000-6fdde000 rw-p 00000000 00:00 0 
6fdde000-6fde9000 r-xp 00000000 b3:0a 81         /usr/lib/lib_SamsungRec_V04001_redwood.so
6fde9000-6fdf1000 ---p 0000b000 b3:0a 81         /usr/lib/lib_SamsungRec_V04001_redwood.so
6fdf1000-6fdf4000 rw-p 0000b000 b3:0a 81         /usr/lib/lib_SamsungRec_V04001_redwood.so
6fdf4000-6fdfd000 rw-p 00000000 00:00 0 
6fdfd000-6fe02000 r-xp 00000000 b3:0a 12453      /usr/lib/libmmfpcmsound.so.0.0.0
6fe02000-6fe09000 ---p 00005000 b3:0a 12453      /usr/lib/libmmfpcmsound.so.0.0.0
6fe09000-6fe0a000 rw-p 00004000 b3:0a 12453      /usr/lib/libmmfpcmsound.so.0.0.0
6fe0a000-6fe0c000 r-xp 00000000 b3:0a 16829      /usr/lib/remix/libtizen_sound_player.so
6fe0c000-6fe13000 ---p 00002000 b3:0a 16829      /usr/lib/remix/libtizen_sound_player.so
6fe13000-6fe14000 rw-p 00001000 b3:0a 16829      /usr/lib/remix/libtizen_sound_player.so
6fe14000-6fe16000 r-xp 00000000 b3:0a 11348      /usr/lib/remix/libeet_sndfile_reader.so
6fe16000-6fe1d000 ---p 00002000 b3:0a 11348      /usr/lib/remix/libeet_sndfile_reader.so
6fe1d000-6fe1e000 rw-p 00001000 b3:0a 11348      /usr/lib/remix/libeet_sndfile_reader.so
6fe1e000-6fe1f000 r-xp 00000000 b3:0a 11342      /usr/lib/edje/modules/multisense_factory/linux-gnueabi-armv7l-1.0.0/module.so
6fe1f000-6fe26000 ---p 00001000 b3:0a 11342      /usr/lib/edje/modules/multisense_factory/linux-gnueabi-armv7l-1.0.0/module.so
6fe26000-6fe27000 rw-p 00000000 b3:0a 11342      /usr/lib/edje/modules/multisense_factory/linux-gnueabi-armv7l-1.0.0/module.so
6fe27000-6fe3e000 r-xp 00000000 b3:0a 11351      /usr/lib/edje/modules/elm/linux-gnueabi-armv7l-1.0.0/module.so
6fe3e000-6fe45000 ---p 00017000 b3:0a 11351      /usr/lib/edje/modules/elm/linux-gnueabi-armv7l-1.0.0/module.so
6fe45000-6fe4a000 rw-p 00016000 b3:0a 11351      /usr/lib/edje/modules/elm/linux-gnueabi-armv7l-1.0.0/module.so
6ff13000-70065000 rw-s 900ec000 00:04 5141       /drm mm object (deleted)
70065000-70096000 rw-p 00000000 00:00 0 
70096000-70aa4000 r--p 00000000 b3:0a 7987       /usr/share/fonts/SDIC_GP_US_20120720.ttf
70aa4000-70ab9000 rw-p 00a0e000 b3:0a 7987       /usr/share/fonts/SDIC_GP_US_20120720.ttf
70ab9000-70ac6000 r--p 00a23000 b3:0a 7987       /usr/share/fonts/SDIC_GP_US_20120720.ttf
70ac6000-70aca000 r--s 00000000 00:15 4849       /tmp/fontconfig/3830d5c3ddfd5cd38a049b759396e72e-le32d8.cache-3
70aca000-70bd4000 r--s 00000000 b3:0a 14607      /usr/apps/com.samsung.di-camera-app/res/edje/nx_style.edj
70bd4000-70c00000 r--p 00000000 07:00 576        /usr/share/locale/en/LC_MESSAGES/di-camera-app.mo
70c00000-70c21000 rw-p 00000000 00:00 0 
70c21000-70d00000 ---p 00000000 00:00 0 
70d04000-70d1c000 r-xp 00000000 b3:0a 8333       /usr/lib/libpng12.so.0.50.0
70d1c000-70d23000 ---p 00018000 b3:0a 8333       /usr/lib/libpng12.so.0.50.0
70d23000-70d24000 rw-p 00017000 b3:0a 8333       /usr/lib/libpng12.so.0.50.0
70d24000-70d26000 r-xp 00000000 b3:0a 11061      /usr/lib/evas/modules/loaders/png/linux-gnueabi-armv7l-1.7.99/module.so
70d26000-70d2d000 ---p 00002000 b3:0a 11061      /usr/lib/evas/modules/loaders/png/linux-gnueabi-armv7l-1.7.99/module.so
70d2d000-70d2e000 rw-p 00001000 b3:0a 11061      /usr/lib/evas/modules/loaders/png/linux-gnueabi-armv7l-1.7.99/module.so
70d2e000-70d2f000 rw-s 06002000 00:05 16         /dev/mem
70d2f000-70d30000 rw-s 10003000 00:05 179        /dev/gpiodev.3
70d30000-70d31000 rw-s 85600000 00:05 16         /dev/mem
70d31000-70d3c000 rw-s 854e0000 00:05 16         /dev/mem
70d3c000-70d3d000 ---p 00000000 00:00 0 
70d3d000-7153c000 rwxp 00000000 00:00 0          [stack:279]
7153c000-7163d000 rw-p 00000000 00:00 0 
7163d000-7163e000 ---p 00000000 00:00 0 
7163e000-71e3d000 rwxp 00000000 00:00 0          [stack:278]
71e3d000-79e3d000 rw-s 99600000 00:05 16         /dev/mem
79e3d000-7b23d000 rw-s 98200000 00:05 16         /dev/mem
7b23d000-7bc3d000 rw-s 97800000 00:05 16         /dev/mem
7bc3d000-7f43d000 rw-s 94000000 00:05 16         /dev/mem
7f43d000-7f43e000 rw-s 85500000 00:05 16         /dev/mem
7f43e000-7f7bf000 rw-s bee79000 00:05 329        /dev/d5_sma
7f7bf000-7f7c0000 ---p 00000000 00:00 0 
7f7c0000-7ffbf000 rwxp 00000000 00:00 0          [stack:266]
7ffbf000-7ffc0000 ---p 00000000 00:00 0 
7ffc0000-807bf000 rwxp 00000000 00:00 0          [stack:265]
807bf000-807c0000 ---p 00000000 00:00 0 
807c0000-80fbf000 rwxp 00000000 00:00 0          [stack:264]
80fbf000-80fc0000 rw-s bbc66000 00:05 16         /dev/mem
80fc0000-81041000 rw-s 85400000 00:05 16         /dev/mem
81041000-81042000 ---p 00000000 00:00 0 
81042000-81841000 rwxp 00000000 00:00 0          [stack:263]
81841000-81842000 ---p 00000000 00:00 0 
81842000-82041000 rwxp 00000000 00:00 0          [stack:262]
82041000-82042000 ---p 00000000 00:00 0 
82042000-82841000 rwxp 00000000 00:00 0          [stack:261]
82841000-82842000 ---p 00000000 00:00 0 
82842000-83041000 rwxp 00000000 00:00 0          [stack:260]
83041000-af041000 rw-s 94000000 00:05 16         /dev/mem
af041000-af042000 ---p 00000000 00:00 0 
af042000-af841000 rwxp 00000000 00:00 0          [stack:259]
af841000-af847000 r-xp 00000000 b3:0a 8782       /usr/lib/libUMP.so
af847000-af84e000 ---p 00006000 b3:0a 8782       /usr/lib/libUMP.so
af84e000-af84f000 rw-p 00005000 b3:0a 8782       /usr/lib/libUMP.so
af84f000-af852000 r-xp 00000000 b3:0a 17264      /usr/lib/bufmgr/libtbm_drime5.so.0.0.0
af852000-af859000 ---p 00003000 b3:0a 17264      /usr/lib/bufmgr/libtbm_drime5.so.0.0.0
af859000-af85a000 rw-p 00002000 b3:0a 17264      /usr/lib/bufmgr/libtbm_drime5.so.0.0.0
af85a000-af85b000 r-xp 00000000 b3:0a 8241       /usr/lib/libdrm_slp.so.1.0.0
af85b000-af862000 ---p 00001000 b3:0a 8241       /usr/lib/libdrm_slp.so.1.0.0
af862000-af863000 rw-p 00000000 b3:0a 8241       /usr/lib/libdrm_slp.so.1.0.0
af863000-af86d000 r-xp 00000000 b3:0a 11053      /usr/lib/evas/modules/engines/software_generic/linux-gnueabi-armv7l-1.7.99/module.so
af86d000-af875000 ---p 0000a000 b3:0a 11053      /usr/lib/evas/modules/engines/software_generic/linux-gnueabi-armv7l-1.7.99/module.so
af875000-af876000 rw-p 0000a000 b3:0a 11053      /usr/lib/evas/modules/engines/software_generic/linux-gnueabi-armv7l-1.7.99/module.so
af876000-af878000 r-xp 00000000 b3:0a 8751       /usr/lib/libdri2.so.0.0.0
af878000-af87f000 ---p 00002000 b3:0a 8751       /usr/lib/libdri2.so.0.0.0
af87f000-af880000 rw-p 00001000 b3:0a 8751       /usr/lib/libdri2.so.0.0.0
af880000-af889000 r-xp 00000000 b3:0a 11054      /usr/lib/evas/modules/engines/software_x11/linux-gnueabi-armv7l-1.7.99/module.so
af889000-af891000 ---p 00009000 b3:0a 11054      /usr/lib/evas/modules/engines/software_x11/linux-gnueabi-armv7l-1.7.99/module.so
af891000-af892000 rw-p 00009000 b3:0a 11054      /usr/lib/evas/modules/engines/software_x11/linux-gnueabi-armv7l-1.7.99/module.so
af892000-af893000 ---p 00000000 00:00 0 
af893000-b0092000 rwxp 00000000 00:00 0          [stack:258]
b0092000-b009c000 r-xp 00000000 b3:0a 3246       /lib/libnss_files-2.13.so
b009c000-b00a3000 ---p 0000a000 b3:0a 3246       /lib/libnss_files-2.13.so
b00a3000-b00a4000 r--p 00009000 b3:0a 3246       /lib/libnss_files-2.13.so
b00a4000-b00a5000 rw-p 0000a000 b3:0a 3246       /lib/libnss_files-2.13.so
b00a9000-b00ac000 r-xp 00000000 b3:0a 8787       /usr/lib/libnative-buffer.so.0.1.0
b00ac000-b00b3000 ---p 00003000 b3:0a 8787       /usr/lib/libnative-buffer.so.0.1.0
b00b3000-b00b4000 rw-p 00002000 b3:0a 8787       /usr/lib/libnative-buffer.so.0.1.0
b00b4000-b017c000 r-xp 00000000 b3:0a 12819      /usr/lib/libscim-1.0.so.8.2.3
b017c000-b018a000 rw-p 000c8000 b3:0a 12819      /usr/lib/libscim-1.0.so.8.2.3
b018a000-b01ae000 r-xp 00000000 b3:0a 12816      /usr/lib/ecore/immodules/libisf-imf-module.so
b01ae000-b01b6000 ---p 00024000 b3:0a 12816      /usr/lib/ecore/immodules/libisf-imf-module.so
b01b6000-b01b7000 rw-p 00024000 b3:0a 12816      /usr/lib/ecore/immodules/libisf-imf-module.so
b01b7000-b01b8000 rw-p 00000000 00:00 0 
b01b8000-b01b9000 r--p 0252a000 07:00 538        /usr/share/locale/locale-archive
b01b9000-b02d8000 r--p 002d4000 07:00 538        /usr/share/locale/locale-archive
b02d8000-b04d8000 r--p 00000000 07:00 538        /usr/share/locale/locale-archive
b04d8000-b04d9000 rw-s 85580000 00:05 16         /dev/mem
b04d9000-b04ea000 rw-s 85480000 00:05 16         /dev/mem
b04ea000-b04f7000 r-xp 00000000 b3:0a 17071      /usr/lib/libslp_devman_plugin.so
b04f7000-b04ff000 ---p 0000d000 b3:0a 17071      /usr/lib/libslp_devman_plugin.so
b04ff000-b0500000 rw-p 0000d000 b3:0a 17071      /usr/lib/libslp_devman_plugin.so
b0500000-b050a000 rw-p 00000000 00:00 0 
b050a000-b050c000 r-xp 00000000 b3:0a 9216       /usr/lib/libsystemd-daemon.so.0.0.10
b050c000-b0513000 ---p 00002000 b3:0a 9216       /usr/lib/libsystemd-daemon.so.0.0.10
b0513000-b0514000 r--p 00001000 b3:0a 9216       /usr/lib/libsystemd-daemon.so.0.0.10
b0514000-b0515000 rw-p 00002000 b3:0a 9216       /usr/lib/libsystemd-daemon.so.0.0.10
b0515000-b052a000 r-xp 00000000 b3:0a 10979      /usr/lib/libpkgmgr_parser.so.0.1.0
b052a000-b0531000 ---p 00015000 b3:0a 10979      /usr/lib/libpkgmgr_parser.so.0.1.0
b0531000-b0532000 rw-p 00014000 b3:0a 10979      /usr/lib/libpkgmgr_parser.so.0.1.0
b0532000-b0534000 r-xp 00000000 b3:0a 12499      /usr/lib/libpkgmgr_installer_status_broadcast_server.so.0.1.0
b0534000-b053b000 ---p 00002000 b3:0a 12499      /usr/lib/libpkgmgr_installer_status_broadcast_server.so.0.1.0
b053b000-b053c000 rw-p 00001000 b3:0a 12499      /usr/lib/libpkgmgr_installer_status_broadcast_server.so.0.1.0
b053c000-b0542000 r-xp 00000000 b3:0a 12497      /usr/lib/libpkgmgr_installer_client.so.0.1.0
b0542000-b054a000 ---p 00006000 b3:0a 12497      /usr/lib/libpkgmgr_installer_client.so.0.1.0
b054a000-b054b000 rw-p 00006000 b3:0a 12497      /usr/lib/libpkgmgr_installer_client.so.0.1.0
b054b000-b054c000 rw-p 00000000 00:00 0 
b054c000-b057b000 r-xp 00000000 b3:0a 12676      /usr/lib/libnfc-common-lib.so.1.0.0
b057b000-b0583000 ---p 0002f000 b3:0a 12676      /usr/lib/libnfc-common-lib.so.1.0.0
b0583000-b0586000 rw-p 0002f000 b3:0a 12676      /usr/lib/libnfc-common-lib.so.1.0.0
b0586000-b0588000 r-xp 00000000 b3:0a 8657       /usr/lib/libXau.so.6.0.0
b0588000-b058f000 ---p 00002000 b3:0a 8657       /usr/lib/libXau.so.6.0.0
b058f000-b0590000 rw-p 00001000 b3:0a 8657       /usr/lib/libXau.so.6.0.0
b0590000-b0596000 r-xp 00000000 b3:0a 9944       /usr/lib/libaudioutil.so.0.0.0
b0596000-b059d000 ---p 00006000 b3:0a 9944       /usr/lib/libaudioutil.so.0.0.0
b059d000-b059e000 rw-p 00005000 b3:0a 9944       /usr/lib/libaudioutil.so.0.0.0
b059e000-b059f000 rw-p 00000000 00:00 0 
b059f000-b05a1000 r-xp 00000000 b3:0a 12738      /usr/lib/libmedia-svc-hash.so.1.0.0
b05a1000-b05a8000 ---p 00002000 b3:0a 12738      /usr/lib/libmedia-svc-hash.so.1.0.0
b05a8000-b05a9000 rw-p 00001000 b3:0a 12738      /usr/lib/libmedia-svc-hash.so.1.0.0
b05a9000-b05ac000 r-xp 00000000 b3:0a 1817       /usr/lib/libuuid.so.1.3.0
b05ac000-b05b3000 ---p 00003000 b3:0a 1817       /usr/lib/libuuid.so.1.3.0
b05b3000-b05b4000 rw-p 00002000 b3:0a 1817       /usr/lib/libuuid.so.1.3.0
b05b4000-b05bf000 r-xp 00000000 b3:0a 10062      /usr/lib/libQdio.so.0.1.0
b05bf000-b05c6000 ---p 0000b000 b3:0a 10062      /usr/lib/libQdio.so.0.1.0
b05c6000-b05c7000 rw-p 0000a000 b3:0a 10062      /usr/lib/libQdio.so.0.1.0
b05c7000-b05d9000 r-xp 00000000 b3:0a 11242      /usr/lib/libcom-core.so.0.0.1
b05d9000-b05e0000 ---p 00012000 b3:0a 11242      /usr/lib/libcom-core.so.0.0.1
b05e0000-b05e1000 rw-p 00011000 b3:0a 11242      /usr/lib/libcom-core.so.0.0.1
b05e1000-b062f000 r-xp 00000000 b3:0a 10967      /usr/lib/libsoup-2.4.so.1.5.0
b062f000-b0636000 ---p 0004e000 b3:0a 10967      /usr/lib/libsoup-2.4.so.1.5.0
b0636000-b0639000 rw-p 0004d000 b3:0a 10967      /usr/lib/libsoup-2.4.so.1.5.0
b0639000-b063a000 rw-p 00000000 00:00 0 
b063a000-b067d000 r-xp 00000000 b3:0a 12665      /usr/lib/libwsm.so
b067d000-b0684000 ---p 00043000 b3:0a 12665      /usr/lib/libwsm.so
b0684000-b07a8000 rw-p 00042000 b3:0a 12665      /usr/lib/libwsm.so
b07a8000-b07c9000 r-xp 00000000 b3:0a 10982      /usr/lib/libpkgmgr-info.so.0.0.17
b07c9000-b07d0000 ---p 00021000 b3:0a 10982      /usr/lib/libpkgmgr-info.so.0.0.17
b07d0000-b07d1000 rw-p 00020000 b3:0a 10982      /usr/lib/libpkgmgr-info.so.0.0.17
b07d1000-b07ea000 r-xp 00000000 b3:0a 12521      /usr/lib/libpkgmgr-client.so.0.1.68
b07ea000-b07f2000 ---p 00019000 b3:0a 12521      /usr/lib/libpkgmgr-client.so.0.1.68
b07f2000-b07f3000 rw-p 00019000 b3:0a 12521      /usr/lib/libpkgmgr-client.so.0.1.68
b07f3000-b0805000 r-xp 00000000 b3:0a 9687       /usr/lib/libsecurity-server-commons.so.1.0.0
b0805000-b080c000 ---p 00012000 b3:0a 9687       /usr/lib/libsecurity-server-commons.so.1.0.0
b080c000-b080d000 rw-p 00011000 b3:0a 9687       /usr/lib/libsecurity-server-commons.so.1.0.0
b080d000-b080e000 rw-p 00000000 00:00 0 
b080e000-b0812000 r-xp 00000000 b3:0a 8399       /usr/lib/libogg.so.0.7.1
b0812000-b0819000 ---p 00004000 b3:0a 8399       /usr/lib/libogg.so.0.7.1
b0819000-b081a000 rw-p 00003000 b3:0a 8399       /usr/lib/libogg.so.0.7.1
b081a000-b083c000 r-xp 00000000 b3:0a 8618       /usr/lib/libvorbis.so.0.4.3
b083c000-b0843000 ---p 00022000 b3:0a 8618       /usr/lib/libvorbis.so.0.4.3
b0843000-b0844000 rw-p 00021000 b3:0a 8618       /usr/lib/libvorbis.so.0.4.3
b0844000-b0928000 r-xp 00000000 b3:0a 8620       /usr/lib/libvorbisenc.so.2.0.6
b0928000-b0930000 ---p 000e4000 b3:0a 8620       /usr/lib/libvorbisenc.so.2.0.6
b0930000-b093c000 rw-p 000e4000 b3:0a 8620       /usr/lib/libvorbisenc.so.2.0.6
b093c000-b096d000 r-xp 00000000 b3:0a 10237      /usr/lib/libFLAC.so.8.2.0
b096d000-b0975000 ---p 00031000 b3:0a 10237      /usr/lib/libFLAC.so.8.2.0
b0975000-b0976000 rw-p 00031000 b3:0a 10237      /usr/lib/libFLAC.so.8.2.0
b0976000-b098c000 r-xp 00000000 b3:0a 8842       /lib/libexpat.so.1.5.2
b098c000-b0993000 ---p 00016000 b3:0a 8842       /lib/libexpat.so.1.5.2
b0993000-b0995000 rw-p 00015000 b3:0a 8842       /lib/libexpat.so.1.5.2
b0995000-b0996000 rw-p 00000000 00:00 0 
b0996000-b09d2000 r-xp 00000000 b3:0a 8209       /usr/lib/libicule.so.52.1
b09d2000-b09d9000 ---p 0003c000 b3:0a 8209       /usr/lib/libicule.so.52.1
b09d9000-b09db000 rw-p 0003b000 b3:0a 8209       /usr/lib/libicule.so.52.1
b09db000-b0aa6000 r-xp 00000000 b3:0a 8178       /usr/lib/libxml2.so.2.7.8
b0aa6000-b0aae000 ---p 000cb000 b3:0a 8178       /usr/lib/libxml2.so.2.7.8
b0aae000-b0ab3000 rw-p 000cb000 b3:0a 8178       /usr/lib/libxml2.so.2.7.8
b0ab3000-b0ab4000 rw-p 00000000 00:00 0 
b0ab4000-b0abd000 r-xp 00000000 b3:0a 8642       /usr/lib/libspdy.so.0.0.0
b0abd000-b0ac5000 ---p 00009000 b3:0a 8642       /usr/lib/libspdy.so.0.0.0
b0ac5000-b0ac6000 rw-p 00009000 b3:0a 8642       /usr/lib/libspdy.so.0.0.0
b0ac6000-b0af4000 r-xp 00000000 b3:0a 8962       /usr/lib/libidn.so.11.5.44
b0af4000-b0afb000 ---p 0002e000 b3:0a 8962       /usr/lib/libidn.so.11.5.44
b0afb000-b0afc000 rw-p 0002d000 b3:0a 8962       /usr/lib/libidn.so.11.5.44
b0afc000-b0afd000 rw-p 00000000 00:00 0 
b0afd000-b0b07000 r-xp 00000000 b3:0a 10233      /usr/lib/libcares.so.2.1.0
b0b07000-b0b0e000 ---p 0000a000 b3:0a 10233      /usr/lib/libcares.so.2.1.0
b0b0e000-b0b0f000 rw-p 00009000 b3:0a 10233      /usr/lib/libcares.so.2.1.0
b0b0f000-b0b42000 r-xp 00000000 b3:0a 12686      /usr/lib/libnfc.so.1.0.0
b0b42000-b0b49000 ---p 00033000 b3:0a 12686      /usr/lib/libnfc.so.1.0.0
b0b49000-b0b4a000 rw-p 00032000 b3:0a 12686      /usr/lib/libnfc.so.1.0.0
b0b4a000-b0b5d000 r-xp 00000000 b3:0a 8720       /usr/lib/libxcb.so.1.1.0
b0b5d000-b0b64000 ---p 00013000 b3:0a 8720       /usr/lib/libxcb.so.1.1.0
b0b64000-b0b65000 rw-p 00012000 b3:0a 8720       /usr/lib/libxcb.so.1.1.0
b0b65000-b0b66000 rw-p 00000000 00:00 0 
b0b66000-b0ba5000 r-xp 00000000 b3:0a 12435      /usr/lib/libbluetooth-api.so.1.0.0
b0ba5000-b0bad000 ---p 0003f000 b3:0a 12435      /usr/lib/libbluetooth-api.so.1.0.0
b0bad000-b0bae000 rw-p 0003f000 b3:0a 12435      /usr/lib/libbluetooth-api.so.1.0.0
b0bae000-b0c1b000 r-xp 00000000 b3:0a 10136      /usr/lib/libwlm_8887.so
b0c1b000-b0c22000 ---p 0006d000 b3:0a 10136      /usr/lib/libwlm_8887.so
b0c22000-b0c24000 rw-p 0006c000 b3:0a 10136      /usr/lib/libwlm_8887.so
b0c24000-b0c25000 rw-p 00000000 00:00 0 
b0c25000-b0c2f000 r-xp 00000000 b3:0a 8391       /usr/lib/libdrm-trusted.so.0.0.57
b0c2f000-b0c37000 ---p 0000a000 b3:0a 8391       /usr/lib/libdrm-trusted.so.0.0.57
b0c37000-b0c38000 rw-p 0000a000 b3:0a 8391       /usr/lib/libdrm-trusted.so.0.0.57
b0c38000-b0c43000 r-xp 00000000 b3:0a 10970      /usr/lib/libdrm-client.so.0.0.102
b0c43000-b0c4a000 ---p 0000b000 b3:0a 10970      /usr/lib/libdrm-client.so.0.0.102
b0c4a000-b0c4b000 rw-p 0000a000 b3:0a 10970      /usr/lib/libdrm-client.so.0.0.102
b0c4b000-b0c5b000 r-xp 00000000 b3:0a 8386       /usr/lib/libsys-mmap-manager.so
b0c5b000-b0c62000 ---p 00010000 b3:0a 8386       /usr/lib/libsys-mmap-manager.so
b0c62000-b0c63000 rw-p 0000f000 b3:0a 8386       /usr/lib/libsys-mmap-manager.so
b0c63000-b0c64000 rw-p 00000000 00:00 0 
b0c64000-b0c66000 r-xp 00000000 b3:0a 10105      /usr/lib/libdi-alg-ipplatform.so
b0c66000-b0c6e000 ---p 00002000 b3:0a 10105      /usr/lib/libdi-alg-ipplatform.so
b0c6e000-b0c6f000 rw-p 00002000 b3:0a 10105      /usr/lib/libdi-alg-ipplatform.so
b0c6f000-b0ce4000 r-xp 00000000 b3:0a 10049      /usr/lib/libredeye.so
b0ce4000-b0ceb000 ---p 00075000 b3:0a 10049      /usr/lib/libredeye.so
b0ceb000-b0ced000 rw-p 00074000 b3:0a 10049      /usr/lib/libredeye.so
b0ced000-b0d8b000 r-xp 00000000 b3:0a 8400       /usr/lib/libsif.so
b0d8b000-b0d93000 ---p 0009e000 b3:0a 8400       /usr/lib/libsif.so
b0d93000-b0d96000 rw-p 0009e000 b3:0a 8400       /usr/lib/libsif.so
b0d96000-b0d9a000 r-xp 00000000 b3:0a 8421       /usr/lib/libmmfosal.so
b0d9a000-b0da1000 ---p 00004000 b3:0a 8421       /usr/lib/libmmfosal.so
b0da1000-b0da2000 rw-p 00003000 b3:0a 8421       /usr/lib/libmmfosal.so
b0da2000-b0de6000 r-xp 00000000 b3:0a 12522      /usr/lib/libmmfmodules.so
b0de6000-b0dee000 ---p 00044000 b3:0a 12522      /usr/lib/libmmfmodules.so
b0dee000-b0df7000 rw-p 00044000 b3:0a 12522      /usr/lib/libmmfmodules.so
b0df7000-b0e05000 rw-p 00000000 00:00 0 
b0e05000-b0e2d000 r-xp 00000000 b3:0a 3578       /usr/lib/libturbojpeg.so
b0e2d000-b0e34000 ---p 00028000 b3:0a 3578       /usr/lib/libturbojpeg.so
b0e34000-b0e35000 rw-p 00027000 b3:0a 3578       /usr/lib/libturbojpeg.so
b0e35000-b0e45000 rw-p 00000000 00:00 0 
b0e45000-b0e4d000 r-xp 00000000 b3:0a 10990      /usr/lib/libmedia-utils.so.0.0.0
b0e4d000-b0e54000 ---p 00008000 b3:0a 10990      /usr/lib/libmedia-utils.so.0.0.0
b0e54000-b0e55000 rw-p 00007000 b3:0a 10990      /usr/lib/libmedia-utils.so.0.0.0
b0e55000-b0e59000 r-xp 00000000 b3:0a 12728      /usr/lib/libmedia-thumbnail.so.1.0.0
b0e59000-b0e61000 ---p 00004000 b3:0a 12728      /usr/lib/libmedia-thumbnail.so.1.0.0
b0e61000-b0e62000 rw-p 00004000 b3:0a 12728      /usr/lib/libmedia-thumbnail.so.1.0.0
b0e62000-b0e7f000 r-xp 00000000 b3:0a 12735      /usr/lib/libmedia-service.so.1.0.0
b0e7f000-b0e86000 ---p 0001d000 b3:0a 12735      /usr/lib/libmedia-service.so.1.0.0
b0e86000-b0e87000 rw-p 0001c000 b3:0a 12735      /usr/lib/libmedia-service.so.1.0.0
b0e87000-b0e88000 rw-p 00000000 00:00 0 
b0e88000-b0e8e000 r-xp 00000000 b3:0a 12930      /usr/lib/libalarm.so.0.0.0
b0e8e000-b0e95000 ---p 00006000 b3:0a 12930      /usr/lib/libalarm.so.0.0.0
b0e95000-b0e96000 rw-p 00005000 b3:0a 12930      /usr/lib/libalarm.so.0.0.0
b0e96000-b0ea5000 r-xp 00000000 b3:0a 12484      /usr/lib/libnotification.so.0.1.0
b0ea5000-b0eac000 ---p 0000f000 b3:0a 12484      /usr/lib/libnotification.so.0.1.0
b0eac000-b0ead000 rw-p 0000e000 b3:0a 12484      /usr/lib/libnotification.so.0.1.0
b0ead000-b0eb3000 r-xp 00000000 b3:0a 12489      /usr/lib/libappsvc.so.0.1.0
b0eb3000-b0eba000 ---p 00006000 b3:0a 12489      /usr/lib/libappsvc.so.0.1.0
b0eba000-b0ebb000 rw-p 00005000 b3:0a 12489      /usr/lib/libappsvc.so.0.1.0
b0ebb000-b0f08000 r-xp 00000000 b3:0a 108        /usr/lib/libudd5.so
b0f08000-b0f0f000 ---p 0004d000 b3:0a 108        /usr/lib/libudd5.so
b0f0f000-b0f11000 rw-p 0004c000 b3:0a 108        /usr/lib/libudd5.so
b0f11000-b0f14000 rw-p 00000000 00:00 0 
b0f14000-b1105000 r-xp 00000000 b3:0a 11335      /usr/lib/libpalm.so
b1105000-b110c000 ---p 001f1000 b3:0a 11335      /usr/lib/libpalm.so
b110c000-b1256000 rw-p 001f0000 b3:0a 11335      /usr/lib/libpalm.so
b1256000-b1322000 rw-p 00000000 00:00 0 
b1322000-b13c2000 r-xp 00000000 b3:0a 11074      /usr/lib/libface.so
b13c2000-b13c9000 ---p 000a0000 b3:0a 11074      /usr/lib/libface.so
b13c9000-b2983000 rw-p 0009f000 b3:0a 11074      /usr/lib/libface.so
b2983000-b29a3000 rw-p 00000000 00:00 0 
b29a3000-b29af000 r-xp 00000000 b3:0a 12664      /usr/lib/libsap-client-stub-api.so.1.0.0
b29af000-b29b6000 ---p 0000c000 b3:0a 12664      /usr/lib/libsap-client-stub-api.so.1.0.0
b29b6000-b29b7000 rw-p 0000b000 b3:0a 12664      /usr/lib/libsap-client-stub-api.so.1.0.0
b29b7000-b29c1000 rw-p 00000000 00:00 0 
b29c1000-b29de000 r-xp 00000000 b3:0a 12661      /usr/lib/libsap-api.so.1.0.0
b29de000-b29e5000 ---p 0001d000 b3:0a 12661      /usr/lib/libsap-api.so.1.0.0
b29e5000-b29e7000 rw-p 0001c000 b3:0a 12661      /usr/lib/libsap-api.so.1.0.0
b29e7000-b2a0a000 r-xp 00000000 b3:0a 12492      /usr/lib/libcapi-network-bluetooth.so.0.1.61
b2a0a000-b2a11000 ---p 00023000 b3:0a 12492      /usr/lib/libcapi-network-bluetooth.so.0.1.61
b2a11000-b2a12000 rw-p 00022000 b3:0a 12492      /usr/lib/libcapi-network-bluetooth.so.0.1.61
b2a12000-b2a13000 rw-p 00000000 00:00 0 
b2a13000-b2a92000 r-xp 00000000 b3:0a 9592       /usr/lib/libdi-network-dlna-rvf.so
b2a92000-b2a99000 ---p 0007f000 b3:0a 9592       /usr/lib/libdi-network-dlna-rvf.so
b2a99000-b2a9b000 rw-p 0007e000 b3:0a 9592       /usr/lib/libdi-network-dlna-rvf.so
b2a9b000-b2aa3000 rw-p 00000000 00:00 0 
b2aa3000-b2ac2000 r-xp 00000000 b3:0a 8037       /usr/lib/libdi-network-dlna-autobackup.so
b2ac2000-b2ac9000 ---p 0001f000 b3:0a 8037       /usr/lib/libdi-network-dlna-autobackup.so
b2ac9000-b2acb000 rw-p 0001e000 b3:0a 8037       /usr/lib/libdi-network-dlna-autobackup.so
b2acb000-b2acc000 rw-p 00000000 00:00 0 
b2acc000-b2bcb000 r-xp 00000000 b3:0a 8015       /usr/lib/libdi-network-dlna-dmsui.so
b2bcb000-b2bd3000 ---p 000ff000 b3:0a 8015       /usr/lib/libdi-network-dlna-dmsui.so
b2bd3000-b2bd7000 rw-p 000ff000 b3:0a 8015       /usr/lib/libdi-network-dlna-dmsui.so
b2bd7000-b2c1c000 r-xp 00000000 b3:0a 9661       /usr/lib/libdi-network-dlna-extlib.so
b2c1c000-b2c23000 ---p 00045000 b3:0a 9661       /usr/lib/libdi-network-dlna-extlib.so
b2c23000-b2c27000 rw-p 00044000 b3:0a 9661       /usr/lib/libdi-network-dlna-extlib.so
b2c27000-b2d8a000 r-xp 00000000 b3:0a 8013       /usr/lib/libdi-network-dlna-stack.so
b2d8a000-b2d92000 ---p 00163000 b3:0a 8013       /usr/lib/libdi-network-dlna-stack.so
b2d92000-b2d97000 rw-p 00163000 b3:0a 8013       /usr/lib/libdi-network-dlna-stack.so
b2d97000-b2da8000 rw-p 00000000 00:00 0 
b2da8000-b2db0000 r-xp 00000000 b3:0a 13830      /usr/lib/libmdm-common.so.1.0.45
b2db0000-b2db7000 ---p 00008000 b3:0a 13830      /usr/lib/libmdm-common.so.1.0.45
b2db7000-b2db8000 rw-p 00007000 b3:0a 13830      /usr/lib/libmdm-common.so.1.0.45
b2db8000-b2dc8000 r-xp 00000000 b3:0a 3256       /lib/libresolv-2.13.so
b2dc8000-b2dc9000 r--p 00010000 b3:0a 3256       /lib/libresolv-2.13.so
b2dc9000-b2dca000 rw-p 00011000 b3:0a 3256       /lib/libresolv-2.13.so
b2dca000-b2dcc000 rw-p 00000000 00:00 0 
b2dcc000-b2dce000 r-xp 00000000 b3:0a 10829      /usr/lib/libgmodule-2.0.so.0.3200.3
b2dce000-b2dd5000 ---p 00002000 b3:0a 10829      /usr/lib/libgmodule-2.0.so.0.3200.3
b2dd5000-b2dd6000 rw-p 00001000 b3:0a 10829      /usr/lib/libgmodule-2.0.so.0.3200.3
b2dd6000-b2ddb000 r-xp 00000000 b3:0a 10455      /usr/lib/libffi.so.5.0.10
b2ddb000-b2de2000 ---p 00005000 b3:0a 10455      /usr/lib/libffi.so.5.0.10
b2de2000-b2de3000 rw-p 00004000 b3:0a 10455      /usr/lib/libffi.so.5.0.10
b2de3000-b2de4000 rw-p 00000000 00:00 0 
b2de4000-b2df9000 r-xp 00000000 b3:0a 9717       /usr/lib/libsecurity-server-client.so.1.0.1
b2df9000-b2e01000 ---p 00015000 b3:0a 9717       /usr/lib/libsecurity-server-client.so.1.0.1
b2e01000-b2e02000 rw-p 00015000 b3:0a 9717       /usr/lib/libsecurity-server-client.so.1.0.1
b2e02000-b2e4a000 r-xp 00000000 b3:0a 11145      /usr/lib/pulseaudio/libpulsecommon-4.0.so
b2e4a000-b2e4b000 rw-p 00048000 b3:0a 11145      /usr/lib/pulseaudio/libpulsecommon-4.0.so
b2e4b000-b2e50000 r-xp 00000000 b3:0a 8381       /usr/lib/libjson.so.0.0.1
b2e50000-b2e57000 ---p 00005000 b3:0a 8381       /usr/lib/libjson.so.0.0.1
b2e57000-b2e58000 rw-p 00004000 b3:0a 8381       /usr/lib/libjson.so.0.0.1
b2e58000-b2e5b000 r-xp 00000000 b3:0a 12428      /usr/lib/libsyspopup_caller.so.0.1.0
b2e5b000-b2e62000 ---p 00003000 b3:0a 12428      /usr/lib/libsyspopup_caller.so.0.1.0
b2e62000-b2e63000 rw-p 00002000 b3:0a 12428      /usr/lib/libsyspopup_caller.so.0.1.0
b2e63000-b2ea8000 r-xp 00000000 b3:0a 10257      /usr/lib/libsndfile.so.1.0.25
b2ea8000-b2eb0000 ---p 00045000 b3:0a 10257      /usr/lib/libsndfile.so.1.0.25
b2eb0000-b2eb2000 rw-p 00045000 b3:0a 10257      /usr/lib/libsndfile.so.1.0.25
b2eb2000-b2eb7000 rw-p 00000000 00:00 0 
b2eb7000-b2ebc000 r-xp 00000000 b3:0a 12457      /usr/lib/libmmfsoundcommon.so.0.0.0
b2ebc000-b2ec3000 ---p 00005000 b3:0a 12457      /usr/lib/libmmfsoundcommon.so.0.0.0
b2ec3000-b2ec4000 rw-p 00004000 b3:0a 12457      /usr/lib/libmmfsoundcommon.so.0.0.0
b2ec4000-b2ec7000 r-xp 00000000 b3:0a 8789       /usr/lib/libXv.so.1.0.0
b2ec7000-b2ece000 ---p 00003000 b3:0a 8789       /usr/lib/libXv.so.1.0.0
b2ece000-b2ecf000 rw-p 00002000 b3:0a 8789       /usr/lib/libXv.so.1.0.0
b2ecf000-b2ed1000 r-xp 00000000 b3:0a 10263      /usr/lib/libctxdata.so.0.0.0
b2ed1000-b2ed8000 ---p 00002000 b3:0a 10263      /usr/lib/libctxdata.so.0.0.0
b2ed8000-b2ed9000 rw-p 00001000 b3:0a 10263      /usr/lib/libctxdata.so.0.0.0
b2ed9000-b2ee6000 r-xp 00000000 b3:0a 10265      /usr/lib/libremix.so.0.0.0
b2ee6000-b2eed000 ---p 0000d000 b3:0a 10265      /usr/lib/libremix.so.0.0.0
b2eed000-b2eee000 rw-p 0000c000 b3:0a 10265      /usr/lib/libremix.so.0.0.0
b2eee000-b2eef000 rw-p 00000000 00:00 0 
b2eef000-b2ef1000 r-xp 00000000 b3:0a 11071      /usr/lib/libecore_imf_evas.so.1.7.99
b2ef1000-b2ef8000 ---p 00002000 b3:0a 11071      /usr/lib/libecore_imf_evas.so.1.7.99
b2ef8000-b2ef9000 rw-p 00001000 b3:0a 11071      /usr/lib/libecore_imf_evas.so.1.7.99
b2ef9000-b2f10000 r-xp 00000000 b3:0a 8948       /usr/lib/liblua-5.1.so
b2f10000-b2f18000 ---p 00017000 b3:0a 8948       /usr/lib/liblua-5.1.so
b2f18000-b2f19000 rw-p 00017000 b3:0a 8948       /usr/lib/liblua-5.1.so
b2f19000-b2f20000 r-xp 00000000 b3:0a 10054      /usr/lib/libembryo.so.1.7.99
b2f20000-b2f27000 ---p 00007000 b3:0a 10054      /usr/lib/libembryo.so.1.7.99
b2f27000-b2f28000 rw-p 00006000 b3:0a 10054      /usr/lib/libembryo.so.1.7.99
b2f28000-b2f7e000 r-xp 00000000 b3:0a 8082       /usr/lib/libpixman-1.so.0.28.2
b2f7e000-b2f86000 ---p 00056000 b3:0a 8082       /usr/lib/libpixman-1.so.0.28.2
b2f86000-b2f8b000 rw-p 00056000 b3:0a 8082       /usr/lib/libpixman-1.so.0.28.2
b2f8b000-b2fae000 r-xp 00000000 b3:0a 8906       /usr/lib/libfontconfig.so.1.5.0
b2fae000-b2fb5000 ---p 00023000 b3:0a 8906       /usr/lib/libfontconfig.so.1.5.0
b2fb5000-b2fb6000 rw-p 00022000 b3:0a 8906       /usr/lib/libfontconfig.so.1.5.0
b2fb6000-b2fb8000 rw-p 00000000 00:00 0 
b2fb8000-b2ffe000 r-xp 00000000 b3:0a 11010      /usr/lib/libharfbuzz.so.0.907.0
b2ffe000-b3006000 ---p 00046000 b3:0a 11010      /usr/lib/libharfbuzz.so.0.907.0
b3006000-b3007000 rw-p 00046000 b3:0a 11010      /usr/lib/libharfbuzz.so.0.907.0
b3007000-b301a000 r-xp 00000000 b3:0a 10172      /usr/lib/libfribidi.so.0.3.1
b301a000-b3021000 ---p 00013000 b3:0a 10172      /usr/lib/libfribidi.so.0.3.1
b3021000-b3022000 rw-p 00012000 b3:0a 10172      /usr/lib/libfribidi.so.0.3.1
b3022000-b3075000 r-xp 00000000 b3:0a 1745       /usr/lib/libfreetype.so.6.8.1
b3075000-b307c000 ---p 00053000 b3:0a 1745       /usr/lib/libfreetype.so.6.8.1
b307c000-b3080000 rw-p 00052000 b3:0a 1745       /usr/lib/libfreetype.so.6.8.1
b3080000-b3084000 r-xp 00000000 b3:0a 11073      /usr/lib/libecore_input_evas.so.1.7.99
b3084000-b308b000 ---p 00004000 b3:0a 11073      /usr/lib/libecore_input_evas.so.1.7.99
b308b000-b308c000 rw-p 00003000 b3:0a 11073      /usr/lib/libecore_input_evas.so.1.7.99
b308c000-b3094000 r-xp 00000000 b3:0a 10965      /usr/lib/libecore_ipc.so.1.7.99
b3094000-b3095000 rw-p 00008000 b3:0a 10965      /usr/lib/libecore_ipc.so.1.7.99
b3095000-b3096000 rw-p 00000000 00:00 0 
b3096000-b309d000 r-xp 00000000 b3:0a 11341      /usr/lib/libecore_fb.so.1.7.99
b309d000-b30a4000 ---p 00007000 b3:0a 11341      /usr/lib/libecore_fb.so.1.7.99
b30a4000-b30a6000 rw-p 00006000 b3:0a 11341      /usr/lib/libecore_fb.so.1.7.99
b30a6000-b30b0000 r-xp 00000000 b3:0a 8728       /usr/lib/libXext.so.6.4.0
b30b0000-b30b7000 ---p 0000a000 b3:0a 8728       /usr/lib/libXext.so.6.4.0
b30b7000-b30b8000 rw-p 00009000 b3:0a 8728       /usr/lib/libXext.so.6.4.0
b30b8000-b30be000 r-xp 00000000 b3:0a 8737       /usr/lib/libXrender.so.1.3.0
b30be000-b30c5000 ---p 00006000 b3:0a 8737       /usr/lib/libXrender.so.1.3.0
b30c5000-b30c6000 rw-p 00005000 b3:0a 8737       /usr/lib/libXrender.so.1.3.0
b30c6000-b30c7000 r-xp 00000000 b3:0a 8827       /usr/lib/libXinerama.so.1.0.0
b30c7000-b30cf000 ---p 00001000 b3:0a 8827       /usr/lib/libXinerama.so.1.0.0
b30cf000-b30d0000 rw-p 00001000 b3:0a 8827       /usr/lib/libXinerama.so.1.0.0
b30d0000-b30d8000 r-xp 00000000 b3:0a 8796       /usr/lib/libXi.so.6.1.0
b30d8000-b30d9000 rw-p 00008000 b3:0a 8796       /usr/lib/libXi.so.6.1.0
b30d9000-b30da000 rw-p 00000000 00:00 0 
b30da000-b30dd000 r-xp 00000000 b3:0a 8754       /usr/lib/libXfixes.so.3.1.0
b30dd000-b30e4000 ---p 00003000 b3:0a 8754       /usr/lib/libXfixes.so.3.1.0
b30e4000-b30e5000 rw-p 00002000 b3:0a 8754       /usr/lib/libXfixes.so.3.1.0
b30e5000-b30e7000 r-xp 00000000 b3:0a 9840       /usr/lib/libXgesture.so.7.0.0
b30e7000-b30ee000 ---p 00002000 b3:0a 9840       /usr/lib/libXgesture.so.7.0.0
b30ee000-b30ef000 rw-p 00001000 b3:0a 9840       /usr/lib/libXgesture.so.7.0.0
b30ef000-b30f0000 r-xp 00000000 b3:0a 8784       /usr/lib/libXdamage.so.1.1.0
b30f0000-b30f8000 ---p 00001000 b3:0a 8784       /usr/lib/libXdamage.so.1.1.0
b30f8000-b30f9000 rw-p 00001000 b3:0a 8784       /usr/lib/libXdamage.so.1.1.0
b30f9000-b30fc000 r-xp 00000000 b3:0a 8182       /usr/lib/libsmack.so.1.0.0
b30fc000-b3103000 ---p 00003000 b3:0a 8182       /usr/lib/libsmack.so.1.0.0
b3103000-b3104000 rw-p 00002000 b3:0a 8182       /usr/lib/libsmack.so.1.0.0
b3104000-b3105000 rw-p 00000000 00:00 0 
b3105000-b3118000 r-xp 00000000 b3:0a 11679      /usr/lib/libsf_common.so
b3118000-b3120000 ---p 00013000 b3:0a 11679      /usr/lib/libsf_common.so
b3120000-b3121000 rw-p 00013000 b3:0a 11679      /usr/lib/libsf_common.so
b3121000-b315e000 r-xp 00000000 b3:0a 10235      /usr/lib/libcurl.so.4.3.0
b315e000-b3165000 ---p 0003d000 b3:0a 10235      /usr/lib/libcurl.so.4.3.0
b3165000-b3167000 rw-p 0003c000 b3:0a 10235      /usr/lib/libcurl.so.4.3.0
b3167000-b3170000 r-xp 00000000 b3:0a 11383      /usr/lib/libethumb.so.1.7.99
b3170000-b3178000 ---p 00009000 b3:0a 11383      /usr/lib/libethumb.so.1.7.99
b3178000-b3179000 rw-p 00009000 b3:0a 11383      /usr/lib/libethumb.so.1.7.99
b3179000-b319c000 r-xp 00000000 b3:0a 3576       /usr/lib/libjpeg.so.8.0.2
b319c000-b31a3000 ---p 00023000 b3:0a 3576       /usr/lib/libjpeg.so.8.0.2
b31a3000-b31a4000 rw-p 00022000 b3:0a 3576       /usr/lib/libjpeg.so.8.0.2
b31a4000-b31b4000 rw-p 00000000 00:00 0 
b31b4000-b31ca000 r-xp 00000000 b3:0a 8173       /lib/libz.so.1.2.5
b31ca000-b31d1000 ---p 00016000 b3:0a 8173       /lib/libz.so.1.2.5
b31d1000-b31d2000 rw-p 00015000 b3:0a 8173       /lib/libz.so.1.2.5
b31d2000-b31d3000 rw-p 00000000 00:00 0 
b31d3000-b31d6000 r-xp 00000000 b3:0a 11662      /usr/lib/libproc-stat.so.0.2.85
b31d6000-b31dd000 ---p 00003000 b3:0a 11662      /usr/lib/libproc-stat.so.0.2.85
b31dd000-b31de000 rw-p 00002000 b3:0a 11662      /usr/lib/libproc-stat.so.0.2.85
b31de000-b31e0000 r-xp 00000000 b3:0a 8839       /usr/lib/libXcomposite.so.1.0.0
b31e0000-b31e7000 ---p 00002000 b3:0a 8839       /usr/lib/libXcomposite.so.1.0.0
b31e7000-b31e8000 rw-p 00001000 b3:0a 8839       /usr/lib/libXcomposite.so.1.0.0
b31e8000-b31ea000 r-xp 00000000 b3:0a 3236       /lib/libdl-2.13.so
b31ea000-b31f1000 ---p 00002000 b3:0a 3236       /lib/libdl-2.13.so
b31f1000-b31f2000 r--p 00001000 b3:0a 3236       /lib/libdl-2.13.so
b31f2000-b31f3000 rw-p 00002000 b3:0a 3236       /lib/libdl-2.13.so
b31f3000-b31fd000 r-xp 00000000 b3:0a 10289      /lib/libunwind.so.8.0.1
b31fd000-b3205000 ---p 0000a000 b3:0a 10289      /lib/libunwind.so.8.0.1
b3205000-b3206000 rw-p 0000a000 b3:0a 10289      /lib/libunwind.so.8.0.1
b3206000-b322b000 rw-p 00000000 00:00 0 
b322b000-b3346000 r-xp 00000000 b3:0a 3230       /lib/libc-2.13.so
b3346000-b334e000 ---p 0011b000 b3:0a 3230       /lib/libc-2.13.so
b334e000-b3350000 r--p 0011b000 b3:0a 3230       /lib/libc-2.13.so
b3350000-b3351000 rw-p 0011d000 b3:0a 3230       /lib/libc-2.13.so
b3351000-b3355000 rw-p 00000000 00:00 0 
b3355000-b335d000 r-xp 00000000 b3:0a 1825       /lib/libgcc_s-4.6.so.1
b335d000-b3364000 ---p 00008000 b3:0a 1825       /lib/libgcc_s-4.6.so.1
b3364000-b3365000 rw-p 00007000 b3:0a 1825       /lib/libgcc_s-4.6.so.1
b3365000-b33ce000 r-xp 00000000 b3:0a 3238       /lib/libm-2.13.so
b33ce000-b33d5000 ---p 00069000 b3:0a 3238       /lib/libm-2.13.so
b33d5000-b33d6000 r--p 00068000 b3:0a 3238       /lib/libm-2.13.so
b33d6000-b33d7000 rw-p 00069000 b3:0a 3238       /lib/libm-2.13.so
b33d7000-b346b000 r-xp 00000000 b3:0a 3560       /usr/lib/libstdc++.so.6.0.16
b346b000-b3473000 ---p 00094000 b3:0a 3560       /usr/lib/libstdc++.so.6.0.16
b3473000-b3476000 r--p 00094000 b3:0a 3560       /usr/lib/libstdc++.so.6.0.16
b3476000-b3478000 rw-p 00097000 b3:0a 3560       /usr/lib/libstdc++.so.6.0.16
b3478000-b347e000 rw-p 00000000 00:00 0 
b347e000-b3492000 r-xp 00000000 b3:0a 3254       /lib/libpthread-2.13.so
b3492000-b3499000 ---p 00014000 b3:0a 3254       /lib/libpthread-2.13.so
b3499000-b349a000 r--p 00013000 b3:0a 3254       /lib/libpthread-2.13.so
b349a000-b349b000 rw-p 00014000 b3:0a 3254       /lib/libpthread-2.13.so
b349b000-b349d000 rw-p 00000000 00:00 0 
b349d000-b349f000 r-xp 00000000 b3:0a 63         /usr/lib/libdlog.so.0.0.0
b349f000-b34a6000 ---p 00002000 b3:0a 63         /usr/lib/libdlog.so.0.0.0
b34a6000-b34a7000 rw-p 00001000 b3:0a 63         /usr/lib/libdlog.so.0.0.0
b34a7000-b34af000 r-xp 00000000 b3:0a 11087      /usr/lib/libdcm.so
b34af000-b34b6000 ---p 00008000 b3:0a 11087      /usr/lib/libdcm.so
b34b6000-b34b7000 rw-p 00007000 b3:0a 11087      /usr/lib/libdcm.so
b34b7000-b34b8000 rw-p 00000000 00:00 0 
b34b8000-b35fb000 r-xp 00000000 b3:0a 8164       /usr/lib/libcrypto.so.1.0.0
b35fb000-b3603000 ---p 00143000 b3:0a 8164       /usr/lib/libcrypto.so.1.0.0
b3603000-b3616000 rw-p 00143000 b3:0a 8164       /usr/lib/libcrypto.so.1.0.0
b3616000-b3619000 rw-p 00000000 00:00 0 
b3619000-b3664000 r-xp 00000000 b3:0a 8165       /usr/lib/libssl.so.1.0.0
b3664000-b366b000 ---p 0004b000 b3:0a 8165       /usr/lib/libssl.so.1.0.0
b366b000-b3670000 rw-p 0004a000 b3:0a 8165       /usr/lib/libssl.so.1.0.0
b3670000-b3676000 r-xp 00000000 b3:0a 3258       /lib/librt-2.13.so
b3676000-b367d000 ---p 00006000 b3:0a 3258       /lib/librt-2.13.so
b367d000-b367e000 r--p 00005000 b3:0a 3258       /lib/librt-2.13.so
b367e000-b367f000 rw-p 00006000 b3:0a 3258       /lib/librt-2.13.so
b367f000-b3680000 r--p 00000000 07:00 581        /usr/share/locale/en/LC_MESSAGES/elementary.mo
b3680000-b3681000 r--p 00000000 07:00 510        /usr/share/locale/en_US/LC_MESSAGES/elementary.mo
b3681000-b3682000 rw-p 00000000 00:00 0 
b3682000-b3683000 rw-s 00000000 00:0d 5030       /dev/shm/sem.7LOrV2 (deleted)
b3683000-b3684000 rw-s 00000000 00:0d 5020       /dev/shm/sem.OArjO1 (deleted)
b3684000-b3685000 rw-s 00000000 00:0d 5019       /dev/shm/sem.KKdSUA (deleted)
b3685000-b3686000 r-xp 00000000 b3:0a 8419       /usr/lib/libbincfg.so.1.1
b3686000-b368d000 ---p 00001000 b3:0a 8419       /usr/lib/libbincfg.so.1.1
b368d000-b368e000 rw-p 00000000 b3:0a 8419       /usr/lib/libbincfg.so.1.1
b368e000-b3690000 r-xp 00000000 b3:0a 83         /usr/lib/liblogutil.so
b3690000-b3697000 ---p 00002000 b3:0a 83         /usr/lib/liblogutil.so
b3697000-b3698000 rw-p 00001000 b3:0a 83         /usr/lib/liblogutil.so
b3698000-b36a1000 r-xp 00000000 b3:0a 8420       /usr/lib/libasl.so
b36a1000-b36a8000 ---p 00009000 b3:0a 8420       /usr/lib/libasl.so
b36a8000-b36a9000 rw-p 00008000 b3:0a 8420       /usr/lib/libasl.so
b36a9000-b37ba000 r-xp 00000000 b3:0a 11238      /usr/lib/libwifi-sns.so
b37ba000-b37c1000 ---p 00111000 b3:0a 11238      /usr/lib/libwifi-sns.so
b37c1000-b37c4000 rw-p 00110000 b3:0a 11238      /usr/lib/libwifi-sns.so
b37c4000-b37dc000 rw-p 00000000 00:00 0 
b37dc000-b37de000 r-xp 00000000 b3:0a 10030      /usr/lib/liboic-tables.so
b37de000-b37e5000 ---p 00002000 b3:0a 10030      /usr/lib/liboic-tables.so
b37e5000-b37e6000 rw-p 00001000 b3:0a 10030      /usr/lib/liboic-tables.so
b37e6000-b37f5000 r-xp 00000000 b3:0a 11320      /usr/lib/libcapi-network-wifi.so.0.1.48
b37f5000-b37fc000 ---p 0000f000 b3:0a 11320      /usr/lib/libcapi-network-wifi.so.0.1.48
b37fc000-b37fd000 rw-p 0000e000 b3:0a 11320      /usr/lib/libcapi-network-wifi.so.0.1.48
b37fd000-b3805000 r-xp 00000000 b3:0a 12695      /usr/lib/libcapi-network-nfc.so.0.1.14
b3805000-b380c000 ---p 00008000 b3:0a 12695      /usr/lib/libcapi-network-nfc.so.0.1.14
b380c000-b380d000 rw-p 00007000 b3:0a 12695      /usr/lib/libcapi-network-nfc.so.0.1.14
b380d000-b387a000 r-xp 00000000 b3:0a 16643      /usr/lib/libdi-alg-prosuggest.so
b387a000-b3881000 ---p 0006d000 b3:0a 16643      /usr/lib/libdi-alg-prosuggest.so
b3881000-b3885000 rw-p 0006c000 b3:0a 16643      /usr/lib/libdi-alg-prosuggest.so
b3885000-b38ff000 rw-p 00000000 00:00 0 
b38ff000-b39e0000 r-xp 00000000 b3:0a 8725       /usr/lib/libX11.so.6.3.0
b39e0000-b39e7000 ---p 000e1000 b3:0a 8725       /usr/lib/libX11.so.6.3.0
b39e7000-b39eb000 rw-p 000e0000 b3:0a 8725       /usr/lib/libX11.so.6.3.0
b39eb000-b39ec000 rw-p 00000000 00:00 0 
b39ec000-b4096000 r-xp 00000000 b3:0a 12678      /usr/lib/libfactory-mode.so
b4096000-b409e000 ---p 006aa000 b3:0a 12678      /usr/lib/libfactory-mode.so
b409e000-b40a0000 rw-p 006aa000 b3:0a 12678      /usr/lib/libfactory-mode.so
b40a0000-b40bd000 rw-p 00000000 00:00 0 
b40bd000-b40c7000 r-xp 00000000 b3:0a 8380       /usr/lib/libmulticore-bridge.so
b40c7000-b40cf000 ---p 0000a000 b3:0a 8380       /usr/lib/libmulticore-bridge.so
b40cf000-b40d0000 rw-p 0000a000 b3:0a 8380       /usr/lib/libmulticore-bridge.so
b40d0000-b40d7000 r-xp 00000000 b3:0a 8389       /usr/lib/libmm-displayer.so
b40d7000-b40de000 ---p 00007000 b3:0a 8389       /usr/lib/libmm-displayer.so
b40de000-b40df000 rw-p 00006000 b3:0a 8389       /usr/lib/libmm-displayer.so
b40df000-b40e1000 r-xp 00000000 b3:0a 11122      /usr/lib/libmmutil_movie.so.0.0.0
b40e1000-b40e8000 ---p 00002000 b3:0a 11122      /usr/lib/libmmutil_movie.so.0.0.0
b40e8000-b40e9000 rw-p 00001000 b3:0a 11122      /usr/lib/libmmutil_movie.so.0.0.0
b40e9000-b41b9000 r-xp 00000000 b3:0a 10827      /usr/lib/libglib-2.0.so.0.3200.3
b41b9000-b41ba000 rw-p 000d0000 b3:0a 10827      /usr/lib/libglib-2.0.so.0.3200.3
b41ba000-b41bb000 rw-p 00000000 00:00 0 
b41bb000-b41c2000 r-xp 00000000 b3:0a 3214       /usr/lib/libmmfcommon.so.0.0.0
b41c2000-b41c9000 ---p 00007000 b3:0a 3214       /usr/lib/libmmfcommon.so.0.0.0
b41c9000-b41ca000 rw-p 00006000 b3:0a 3214       /usr/lib/libmmfcommon.so.0.0.0
b41ca000-b41dc000 r-xp 00000000 b3:0a 12612      /usr/lib/libmmfile_utils.so.0.0.0
b41dc000-b41e3000 ---p 00012000 b3:0a 12612      /usr/lib/libmmfile_utils.so.0.0.0
b41e3000-b41e4000 rw-p 00011000 b3:0a 12612      /usr/lib/libmmfile_utils.so.0.0.0
b41e4000-b41e9000 r-xp 00000000 b3:0a 12603      /usr/lib/libmmffile.so.0.0.0
b41e9000-b41f1000 ---p 00005000 b3:0a 12603      /usr/lib/libmmffile.so.0.0.0
b41f1000-b41f2000 rw-p 00005000 b3:0a 12603      /usr/lib/libmmffile.so.0.0.0
b41f2000-b4212000 r-xp 00000000 b3:0a 11636      /usr/lib/libmm-slideshow.so
b4212000-b4213000 rw-p 00020000 b3:0a 11636      /usr/lib/libmm-slideshow.so
b4213000-b4305000 r-xp 00000000 b3:0a 11635      /usr/lib/libmm-photo.so
b4305000-b430d000 ---p 000f2000 b3:0a 11635      /usr/lib/libmm-photo.so
b430d000-b430f000 rw-p 000f2000 b3:0a 11635      /usr/lib/libmm-photo.so
b430f000-b4311000 rw-p 00000000 00:00 0 
b4311000-b4314000 r-xp 00000000 b3:0a 8609       /usr/lib/libmm_ta.so.0.0.0
b4314000-b431b000 ---p 00003000 b3:0a 8609       /usr/lib/libmm_ta.so.0.0.0
b431b000-b431c000 rw-p 00002000 b3:0a 8609       /usr/lib/libmm_ta.so.0.0.0
b431c000-b431d000 rw-p 00000000 00:00 0 
b431d000-b4340000 r-xp 00000000 b3:0a 8606       /usr/lib/libexif.so.12.3.3
b4340000-b4347000 ---p 00023000 b3:0a 8606       /usr/lib/libexif.so.12.3.3
b4347000-b4354000 rw-p 00022000 b3:0a 8606       /usr/lib/libexif.so.12.3.3
b4354000-b43a6000 r-xp 00000000 b3:0a 12594      /usr/lib/libmmfcore.so
b43a6000-b43ad000 ---p 00052000 b3:0a 12594      /usr/lib/libmmfcore.so
b43ad000-b43af000 rw-p 00051000 b3:0a 12594      /usr/lib/libmmfcore.so
b43af000-b43bf000 r-xp 00000000 b3:0a 12595      /usr/lib/libmmf-camcorder.so
b43bf000-b43c2000 rw-p 00010000 b3:0a 12595      /usr/lib/libmmf-camcorder.so
b43c2000-b43d5000 r-xp 00000000 b3:0a 12596      /usr/lib/libmmf_player.so
b43d5000-b43dd000 ---p 00013000 b3:0a 12596      /usr/lib/libmmf_player.so
b43dd000-b43de000 rw-p 00013000 b3:0a 12596      /usr/lib/libmmf_player.so
b43de000-b43e3000 r-xp 00000000 b3:0a 1552       /usr/lib/libmm-type.so
b43e3000-b43ea000 ---p 00005000 b3:0a 1552       /usr/lib/libmm-type.so
b43ea000-b43eb000 rw-p 00004000 b3:0a 1552       /usr/lib/libmm-type.so
b43eb000-b4428000 r-xp 00000000 b3:0a 3550       /usr/lib/libtint-util.so
b4428000-b4430000 ---p 0003d000 b3:0a 3550       /usr/lib/libtint-util.so
b4430000-b4431000 rw-p 0003d000 b3:0a 3550       /usr/lib/libtint-util.so
b4431000-b4432000 rw-p 00000000 00:00 0 
b4432000-b4436000 r-xp 00000000 b3:0a 8360       /usr/lib/libmicom-node.so.0.1
b4436000-b443d000 ---p 00004000 b3:0a 8360       /usr/lib/libmicom-node.so.0.1
b443d000-b443e000 rw-p 00003000 b3:0a 8360       /usr/lib/libmicom-node.so.0.1
b443e000-b4448000 r-xp 00000000 b3:0a 11345      /usr/lib/libdeviced.so.0.1.0
b4448000-b444f000 ---p 0000a000 b3:0a 11345      /usr/lib/libdeviced.so.0.1.0
b444f000-b4450000 rw-p 00009000 b3:0a 11345      /usr/lib/libdeviced.so.0.1.0
b4450000-b4455000 r-xp 00000000 b3:0a 10882      /usr/lib/libdevice-node.so.0.1
b4455000-b445c000 ---p 00005000 b3:0a 10882      /usr/lib/libdevice-node.so.0.1
b445c000-b445d000 rw-p 00004000 b3:0a 10882      /usr/lib/libdevice-node.so.0.1
b445d000-b4472000 r-xp 00000000 b3:0a 12919      /usr/lib/libshell-command.so
b4472000-b447a000 ---p 00015000 b3:0a 12919      /usr/lib/libshell-command.so
b447a000-b447d000 rw-p 00015000 b3:0a 12919      /usr/lib/libshell-command.so
b447d000-b4493000 r-xp 00000000 b3:0a 11085      /usr/lib/libfilelist-manager.so
b4493000-b449a000 ---p 00016000 b3:0a 11085      /usr/lib/libfilelist-manager.so
b449a000-b449b000 rw-p 00015000 b3:0a 11085      /usr/lib/libfilelist-manager.so
b449b000-b449c000 rw-p 00000000 00:00 0 
b449c000-b44c4000 r-xp 00000000 b3:0a 12741      /usr/lib/libcapi-content-media-content.so.0.2.108
b44c4000-b44cb000 ---p 00028000 b3:0a 12741      /usr/lib/libcapi-content-media-content.so.0.2.108
b44cb000-b44cc000 rw-p 00027000 b3:0a 12741      /usr/lib/libcapi-content-media-content.so.0.2.108
b44cc000-b44d9000 r-xp 00000000 b3:0a 12932      /usr/lib/libcapi-appfw-application.so.0.1.6
b44d9000-b44e0000 ---p 0000d000 b3:0a 12932      /usr/lib/libcapi-appfw-application.so.0.1.6
b44e0000-b44e2000 rw-p 0000c000 b3:0a 12932      /usr/lib/libcapi-appfw-application.so.0.1.6
b44e2000-b44ea000 r-xp 00000000 b3:0a 1716       /usr/lib/libdiosal.so
b44ea000-b44eb000 rw-p 00008000 b3:0a 1716       /usr/lib/libdiosal.so
b44eb000-b44f5000 r-xp 00000000 b3:0a 12698      /usr/lib/libdi-sensor.so
b44f5000-b44fc000 ---p 0000a000 b3:0a 12698      /usr/lib/libdi-sensor.so
b44fc000-b44fd000 rw-p 00009000 b3:0a 12698      /usr/lib/libdi-sensor.so
b44fd000-b44fe000 r-xp 00000000 b3:0a 11713      /usr/lib/libsystem-tools.so
b44fe000-b4505000 ---p 00001000 b3:0a 11713      /usr/lib/libsystem-tools.so
b4505000-b4506000 rw-p 00000000 b3:0a 11713      /usr/lib/libsystem-tools.so
b4506000-b4507000 rw-p 00000000 00:00 0 
b4507000-b4511000 r-xp 00000000 b3:0a 8133       /usr/lib/libfirmware-upgrade.so
b4511000-b4519000 ---p 0000a000 b3:0a 8133       /usr/lib/libfirmware-upgrade.so
b4519000-b451a000 rw-p 0000a000 b3:0a 8133       /usr/lib/libfirmware-upgrade.so
b451a000-b451d000 r-xp 00000000 b3:0a 8731       /usr/lib/libXtst.so.6.1.0
b451d000-b4524000 ---p 00003000 b3:0a 8731       /usr/lib/libXtst.so.6.1.0
b4524000-b4525000 rw-p 00002000 b3:0a 8731       /usr/lib/libXtst.so.6.1.0
b4525000-b4529000 r-xp 00000000 b3:0a 10089      /usr/lib/libhdmi-cec.so
b4529000-b4531000 ---p 00004000 b3:0a 10089      /usr/lib/libhdmi-cec.so
b4531000-b4532000 rw-p 00004000 b3:0a 10089      /usr/lib/libhdmi-cec.so
b4532000-b4537000 r-xp 00000000 b3:0a 8744       /usr/lib/libXrandr.so.2.2.0
b4537000-b453e000 ---p 00005000 b3:0a 8744       /usr/lib/libXrandr.so.2.2.0
b453e000-b453f000 rw-p 00004000 b3:0a 8744       /usr/lib/libXrandr.so.2.2.0
b453f000-b4543000 r-xp 00000000 b3:0a 1554       /usr/lib/libversion-info.so
b4543000-b454b000 ---p 00004000 b3:0a 1554       /usr/lib/libversion-info.so
b454b000-b454c000 rw-p 00004000 b3:0a 1554       /usr/lib/libversion-info.so
b454c000-b457b000 r-xp 00000000 b3:0a 8417       /usr/lib/libuser-spec.so
b457b000-b4583000 ---p 0002f000 b3:0a 8417       /usr/lib/libuser-spec.so
b4583000-b4584000 rw-p 0002f000 b3:0a 8417       /usr/lib/libuser-spec.so
b4584000-b4589000 rw-p 00000000 00:00 0 
b4589000-b4bdb000 r-xp 00000000 b3:0a 1715       /usr/lib/libprefman.so
b4bdb000-b4be3000 ---p 00652000 b3:0a 1715       /usr/lib/libprefman.so
b4be3000-b4be4000 rw-p 00652000 b3:0a 1715       /usr/lib/libprefman.so
b4be4000-b4be8000 r-xp 00000000 b3:0a 11112      /usr/lib/libsysman.so.0.2.0
b4be8000-b4bef000 ---p 00004000 b3:0a 11112      /usr/lib/libsysman.so.0.2.0
b4bef000-b4bf0000 rw-p 00003000 b3:0a 11112      /usr/lib/libsysman.so.0.2.0
b4bf0000-b4ca0000 r-xp 00000000 b3:0a 11337      /usr/lib/libcapture-fw-prod.so
b4ca0000-b4ca3000 rw-p 000b0000 b3:0a 11337      /usr/lib/libcapture-fw-prod.so
b4ca3000-b4ca4000 rw-p 00000000 00:00 0 
b4ca4000-b4ceb000 r-xp 00000000 b3:0a 12688      /usr/lib/libdi-network-bt-app.so
b4ceb000-b4cf2000 ---p 00047000 b3:0a 12688      /usr/lib/libdi-network-bt-app.so
b4cf2000-b4cf3000 rw-p 00046000 b3:0a 12688      /usr/lib/libdi-network-bt-app.so
b4cf3000-b4cf7000 rw-p 00000000 00:00 0 
b4cf7000-b4d71000 r-xp 00000000 b3:0a 9683       /usr/lib/libdi-network-dlna-api.so
b4d71000-b4d78000 ---p 0007a000 b3:0a 9683       /usr/lib/libdi-network-dlna-api.so
b4d78000-b4d7a000 rw-p 00079000 b3:0a 9683       /usr/lib/libdi-network-dlna-api.so
b4d7a000-b4d7d000 rw-p 00000000 00:00 0 
b4d7d000-b4d7f000 r-xp 00000000 b3:0a 8246       /usr/lib/libiniparser.so.0
b4d7f000-b4d87000 ---p 00002000 b3:0a 8246       /usr/lib/libiniparser.so.0
b4d87000-b4d88000 rw-p 00002000 b3:0a 8246       /usr/lib/libiniparser.so.0
b4d88000-b4d89000 rw-p 00000000 00:00 0 
b4d89000-b4dbd000 r-xp 00000000 b3:0a 10831      /usr/lib/libgobject-2.0.so.0.3200.3
b4dbd000-b4dc4000 ---p 00034000 b3:0a 10831      /usr/lib/libgobject-2.0.so.0.3200.3
b4dc4000-b4dc6000 rw-p 00033000 b3:0a 10831      /usr/lib/libgobject-2.0.so.0.3200.3
b4dc6000-b4df0000 r-xp 00000000 b3:0a 8947       /usr/lib/libdbus-1.so.3.7.2
b4df0000-b4df8000 ---p 0002a000 b3:0a 8947       /usr/lib/libdbus-1.so.3.7.2
b4df8000-b4df9000 rw-p 0002a000 b3:0a 8947       /usr/lib/libdbus-1.so.3.7.2
b4df9000-b4dfc000 r-xp 00000000 b3:0a 10993      /usr/lib/libcsc-feature.so.0.0.0
b4dfc000-b4e03000 ---p 00003000 b3:0a 10993      /usr/lib/libcsc-feature.so.0.0.0
b4e03000-b4e04000 rw-p 00002000 b3:0a 10993      /usr/lib/libcsc-feature.so.0.0.0
b4e04000-b4e12000 r-xp 00000000 b3:0a 15417      /usr/lib/libmdm.so.1.0.88
b4e12000-b4e1a000 ---p 0000e000 b3:0a 15417      /usr/lib/libmdm.so.1.0.88
b4e1a000-b4e1b000 rw-p 0000e000 b3:0a 15417      /usr/lib/libmdm.so.1.0.88
b4e1b000-b4e20000 r-xp 00000000 b3:0a 8393       /usr/lib/libss-client.so.1.0.0
b4e20000-b4e27000 ---p 00005000 b3:0a 8393       /usr/lib/libss-client.so.1.0.0
b4e27000-b4e28000 rw-p 00004000 b3:0a 8393       /usr/lib/libss-client.so.1.0.0
b4e28000-b4e29000 rw-p 00000000 00:00 0 
b4e29000-b4e30000 r-xp 00000000 b3:0a 10848      /usr/lib/libvconf.so.0.2.45
b4e30000-b4e38000 ---p 00007000 b3:0a 10848      /usr/lib/libvconf.so.0.2.45
b4e38000-b4e39000 rw-p 00007000 b3:0a 10848      /usr/lib/libvconf.so.0.2.45
b4e39000-b4e50000 r-xp 00000000 b3:0a 10870      /usr/lib/libdbus-glib-1.so.2.2.2
b4e50000-b4e58000 ---p 00017000 b3:0a 10870      /usr/lib/libdbus-glib-1.so.2.2.2
b4e58000-b4e59000 rw-p 00017000 b3:0a 10870      /usr/lib/libdbus-glib-1.so.2.2.2
b4e59000-b4e6b000 r-xp 00000000 b3:0a 11077      /usr/lib/libcapi-network-tethering.so.0.1.0
b4e6b000-b4e73000 ---p 00012000 b3:0a 11077      /usr/lib/libcapi-network-tethering.so.0.1.0
b4e73000-b4e74000 rw-p 00012000 b3:0a 11077      /usr/lib/libcapi-network-tethering.so.0.1.0
b4e74000-b4e8a000 r-xp 00000000 b3:0a 11004      /usr/lib/libwifi-direct.so.0.0
b4e8a000-b4e91000 ---p 00016000 b3:0a 11004      /usr/lib/libwifi-direct.so.0.0
b4e91000-b4e92000 rw-p 00015000 b3:0a 11004      /usr/lib/libwifi-direct.so.0.0
b4e92000-b4e93000 r-xp 00000000 b3:0a 10833      /usr/lib/libgthread-2.0.so.0.3200.3
b4e93000-b4e9a000 ---p 00001000 b3:0a 10833      /usr/lib/libgthread-2.0.so.0.3200.3
b4e9a000-b4e9b000 rw-p 00000000 b3:0a 10833      /usr/lib/libgthread-2.0.so.0.3200.3
b4e9b000-b4e9c000 rw-p 00000000 00:00 0 
b4e9c000-b4f70000 r-xp 00000000 b3:0a 10825      /usr/lib/libgio-2.0.so.0.3200.3
b4f70000-b4f78000 ---p 000d4000 b3:0a 10825      /usr/lib/libgio-2.0.so.0.3200.3
b4f78000-b4f7b000 rw-p 000d4000 b3:0a 10825      /usr/lib/libgio-2.0.so.0.3200.3
b4f7b000-b4f7c000 rw-p 00000000 00:00 0 
b4f7c000-b4f9e000 r-xp 00000000 b3:0a 10986      /usr/lib/libnetwork.so.0.0.0
b4f9e000-b4fa5000 ---p 00022000 b3:0a 10986      /usr/lib/libnetwork.so.0.0.0
b4fa5000-b4fa6000 rw-p 00021000 b3:0a 10986      /usr/lib/libnetwork.so.0.0.0
b4fa6000-b4fad000 r-xp 00000000 b3:0a 8234       /usr/lib/libdrm.so.2.4.0
b4fad000-b4fb5000 ---p 00007000 b3:0a 8234       /usr/lib/libdrm.so.2.4.0
b4fb5000-b4fb6000 rw-p 00007000 b3:0a 8234       /usr/lib/libdrm.so.2.4.0
b4fb6000-b4fb9000 r-xp 00000000 b3:0a 8243       /usr/lib/libtbm.so.1.0.0
b4fb9000-b4fc0000 ---p 00003000 b3:0a 8243       /usr/lib/libtbm.so.1.0.0
b4fc0000-b4fc1000 rw-p 00002000 b3:0a 8243       /usr/lib/libtbm.so.1.0.0
b4fc1000-b4fc6000 r-xp 00000000 b3:0a 11098      /usr/lib/libhibernation.so
b4fc6000-b4fcd000 ---p 00005000 b3:0a 11098      /usr/lib/libhibernation.so
b4fcd000-b4fce000 rw-p 00004000 b3:0a 11098      /usr/lib/libhibernation.so
b4fce000-b4fcf000 rw-p 00000000 00:00 0 
b4fcf000-b4fd9000 r-xp 00000000 b3:0a 10922      /usr/lib/libaudio-session-mgr.so.0.0.0
b4fd9000-b4fe1000 ---p 0000a000 b3:0a 10922      /usr/lib/libaudio-session-mgr.so.0.0.0
b4fe1000-b4fe2000 rw-p 0000a000 b3:0a 10922      /usr/lib/libaudio-session-mgr.so.0.0.0
b4fe2000-b4fe6000 rw-p 00000000 00:00 0 
b4fe6000-b501d000 r-xp 00000000 b3:0a 11144      /usr/lib/libpulse.so.0.16.2
b501d000-b5024000 ---p 00037000 b3:0a 11144      /usr/lib/libpulse.so.0.16.2
b5024000-b5025000 rw-p 00036000 b3:0a 11144      /usr/lib/libpulse.so.0.16.2
b5025000-b5085000 r-xp 00000000 b3:0a 8256       /usr/lib/libasound.so.2.0.0
b5085000-b508c000 ---p 00060000 b3:0a 8256       /usr/lib/libasound.so.2.0.0
b508c000-b508f000 rw-p 0005f000 b3:0a 8256       /usr/lib/libasound.so.2.0.0
b508f000-b5092000 r-xp 00000000 b3:0a 11142      /usr/lib/libpulse-simple.so.0.0.4
b5092000-b5099000 ---p 00003000 b3:0a 11142      /usr/lib/libpulse-simple.so.0.0.4
b5099000-b509a000 rw-p 00002000 b3:0a 11142      /usr/lib/libpulse-simple.so.0.0.4
b509a000-b509f000 r-xp 00000000 b3:0a 8036       /usr/lib/libascenario-0.2.so.0.0.0
b509f000-b50a6000 ---p 00005000 b3:0a 8036       /usr/lib/libascenario-0.2.so.0.0.0
b50a6000-b50a7000 rw-p 00004000 b3:0a 8036       /usr/lib/libascenario-0.2.so.0.0.0
b50a7000-b50ab000 r-xp 00000000 b3:0a 10928      /usr/lib/libmmfsession.so.0.0.0
b50ab000-b50b3000 ---p 00004000 b3:0a 10928      /usr/lib/libmmfsession.so.0.0.0
b50b3000-b50b4000 rw-p 00004000 b3:0a 10928      /usr/lib/libmmfsession.so.0.0.0
b50b4000-b50ce000 r-xp 00000000 b3:0a 11235      /usr/lib/libavsysaudio.so.0.0.1
b50ce000-b50d5000 ---p 0001a000 b3:0a 11235      /usr/lib/libavsysaudio.so.0.0.1
b50d5000-b50d6000 rw-p 00019000 b3:0a 11235      /usr/lib/libavsysaudio.so.0.0.1
b50d6000-b50d7000 rw-p 00000000 00:00 0 
b50d7000-b50ee000 r-xp 00000000 b3:0a 12455      /usr/lib/libmmfsound.so.0.1.0
b50ee000-b50f5000 ---p 00017000 b3:0a 12455      /usr/lib/libmmfsound.so.0.1.0
b50f5000-b50f6000 rw-p 00016000 b3:0a 12455      /usr/lib/libmmfsound.so.0.1.0
b50f6000-b50ff000 r-xp 00000000 b3:0a 10910      /usr/lib/libutilX.so.1.1.0
b50ff000-b5106000 ---p 00009000 b3:0a 10910      /usr/lib/libutilX.so.1.1.0
b5106000-b5107000 rw-p 00008000 b3:0a 10910      /usr/lib/libutilX.so.1.1.0
b5107000-b5111000 r-xp 00000000 b3:0a 8416       /usr/lib/libapex.so
b5111000-b5118000 ---p 0000a000 b3:0a 8416       /usr/lib/libapex.so
b5118000-b5119000 rw-p 00009000 b3:0a 8416       /usr/lib/libapex.so
b5119000-b512e000 r-xp 00000000 b3:0a 11378      /usr/lib/libgui.so
b512e000-b5135000 ---p 00015000 b3:0a 11378      /usr/lib/libgui.so
b5135000-b5136000 rw-p 00014000 b3:0a 11378      /usr/lib/libgui.so
b5136000-b5139000 rw-p 00000000 00:00 0 
b5139000-b5141000 r-xp 00000000 b3:0a 8021       /usr/lib/libdi-elementary.so
b5141000-b5148000 ---p 00008000 b3:0a 8021       /usr/lib/libdi-elementary.so
b5148000-b5149000 rw-p 00007000 b3:0a 8021       /usr/lib/libdi-elementary.so
b5149000-b5187000 r-xp 00000000 b3:0a 349        /usr/lib/libeina.so.1.7.99
b5187000-b518e000 ---p 0003e000 b3:0a 349        /usr/lib/libeina.so.1.7.99
b518e000-b5190000 rw-p 0003d000 b3:0a 349        /usr/lib/libeina.so.1.7.99
b5190000-b51eb000 r-xp 00000000 b3:0a 11347      /usr/lib/libedje.so.1.7.99
b51eb000-b51f2000 ---p 0005b000 b3:0a 11347      /usr/lib/libedje.so.1.7.99
b51f2000-b51f4000 rw-p 0005a000 b3:0a 11347      /usr/lib/libedje.so.1.7.99
b51f4000-b529f000 r-xp 00000000 b3:0a 11067      /usr/lib/libevas.so.1.7.99
b529f000-b52a6000 ---p 000ab000 b3:0a 11067      /usr/lib/libevas.so.1.7.99
b52a6000-b52b1000 rw-p 000aa000 b3:0a 11067      /usr/lib/libevas.so.1.7.99
b52b1000-b52c3000 rw-p 00000000 00:00 0 
b52c3000-b52d4000 r-xp 00000000 b3:0a 10873      /usr/lib/libecore_input.so.1.7.99
b52d4000-b52db000 ---p 00011000 b3:0a 10873      /usr/lib/libecore_input.so.1.7.99
b52db000-b52dc000 rw-p 00010000 b3:0a 10873      /usr/lib/libecore_input.so.1.7.99
b52dc000-b5311000 r-xp 00000000 b3:0a 11344      /usr/lib/libecore_evas.so.1.7.99
b5311000-b5318000 ---p 00035000 b3:0a 11344      /usr/lib/libecore_evas.so.1.7.99
b5318000-b531a000 rw-p 00034000 b3:0a 11344      /usr/lib/libecore_evas.so.1.7.99
b531a000-b5367000 r-xp 00000000 b3:0a 10875      /usr/lib/libecore_x.so.1.7.99
b5367000-b536e000 ---p 0004d000 b3:0a 10875      /usr/lib/libecore_x.so.1.7.99
b536e000-b5370000 rw-p 0004c000 b3:0a 10875      /usr/lib/libecore_x.so.1.7.99
b5370000-b5398000 r-xp 00000000 b3:0a 10853      /usr/lib/libecore.so.1.7.99
b5398000-b5399000 rw-p 00028000 b3:0a 10853      /usr/lib/libecore.so.1.7.99
b5399000-b53a7000 rw-p 00000000 00:00 0 
b53a7000-b6a12000 r--p 00000000 b3:0a 8200       /usr/lib/libicudata.so.52.1
b6a12000-b6a19000 ---p 0166b000 b3:0a 8200       /usr/lib/libicudata.so.52.1
b6a19000-b6a1a000 rw-p 0166a000 b3:0a 8200       /usr/lib/libicudata.so.52.1
b6a1a000-b6b03000 r-xp 00000000 b3:0a 8221       /usr/lib/libicuuc.so.52.1
b6b03000-b6b0a000 ---p 000e9000 b3:0a 8221       /usr/lib/libicuuc.so.52.1
b6b0a000-b6b13000 rw-p 000e8000 b3:0a 8221       /usr/lib/libicuuc.so.52.1
b6b13000-b6b18000 rw-p 00000000 00:00 0 
b6b18000-b6c5f000 r-xp 00000000 b3:0a 8203       /usr/lib/libicui18n.so.52.1
b6c5f000-b6c67000 ---p 00147000 b3:0a 8203       /usr/lib/libicui18n.so.52.1
b6c67000-b6c6f000 rw-p 00147000 b3:0a 8203       /usr/lib/libicui18n.so.52.1
b6c6f000-b6cd4000 r-xp 00000000 b3:0a 8148       /usr/lib/libsqlite3.so.0.8.6
b6cd4000-b6cdb000 ---p 00065000 b3:0a 8148       /usr/lib/libsqlite3.so.0.8.6
b6cdb000-b6cde000 rw-p 00064000 b3:0a 8148       /usr/lib/libsqlite3.so.0.8.6
b6cde000-b6ce1000 r-xp 00000000 b3:0a 10878      /usr/lib/libSLP-db-util.so.0.1.0
b6ce1000-b6ce8000 ---p 00003000 b3:0a 10878      /usr/lib/libSLP-db-util.so.0.1.0
b6ce8000-b6ce9000 rw-p 00002000 b3:0a 10878      /usr/lib/libSLP-db-util.so.0.1.0
b6ce9000-b6cee000 r-xp 00000000 b3:0a 8020       /usr/lib/libxdgmime.so.1.1.0
b6cee000-b6cf6000 ---p 00005000 b3:0a 8020       /usr/lib/libxdgmime.so.1.1.0
b6cf6000-b6cf7000 rw-p 00005000 b3:0a 8020       /usr/lib/libxdgmime.so.1.1.0
b6cf7000-b6d04000 r-xp 00000000 b3:0a 10918      /usr/lib/libail.so.0.1.0
b6d04000-b6d0b000 ---p 0000d000 b3:0a 10918      /usr/lib/libail.so.0.1.0
b6d0b000-b6d0c000 rw-p 0000c000 b3:0a 10918      /usr/lib/libail.so.0.1.0
b6d0c000-b6d0f000 r-xp 00000000 b3:0a 10868      /usr/lib/libbundle.so.0.1.22
b6d0f000-b6d16000 ---p 00003000 b3:0a 10868      /usr/lib/libbundle.so.0.1.22
b6d16000-b6d17000 rw-p 00002000 b3:0a 10868      /usr/lib/libbundle.so.0.1.22
b6d17000-b6d23000 r-xp 00000000 b3:0a 12400      /usr/lib/libaul.so.0.1.0
b6d23000-b6d2b000 ---p 0000c000 b3:0a 12400      /usr/lib/libaul.so.0.1.0
b6d2b000-b6d2c000 rw-p 0000c000 b3:0a 12400      /usr/lib/libaul.so.0.1.0
b6d2c000-b6d40000 r-xp 00000000 b3:0a 11678      /usr/lib/libsensor.so.1.1.0
b6d40000-b6d47000 ---p 00014000 b3:0a 11678      /usr/lib/libsensor.so.1.1.0
b6d47000-b6d49000 rw-p 00013000 b3:0a 11678      /usr/lib/libsensor.so.1.1.0
b6d49000-b6d4d000 r-xp 00000000 b3:0a 12426      /usr/lib/libappcore-common.so.1.1
b6d4d000-b6d54000 ---p 00004000 b3:0a 12426      /usr/lib/libappcore-common.so.1.1
b6d54000-b6d55000 rw-p 00003000 b3:0a 12426      /usr/lib/libappcore-common.so.1.1
b6d55000-b6d8e000 r-xp 00000000 b3:0a 10890      /usr/lib/libecore_con.so.1.7.99
b6d8e000-b6d95000 ---p 00039000 b3:0a 10890      /usr/lib/libecore_con.so.1.7.99
b6d95000-b6d97000 rw-p 00038000 b3:0a 10890      /usr/lib/libecore_con.so.1.7.99
b6d97000-b6d9f000 r-xp 00000000 b3:0a 10888      /usr/lib/libecore_imf.so.1.7.99
b6d9f000-b6da6000 ---p 00008000 b3:0a 10888      /usr/lib/libecore_imf.so.1.7.99
b6da6000-b6da7000 rw-p 00007000 b3:0a 10888      /usr/lib/libecore_imf.so.1.7.99
b6da7000-b6daf000 r-xp 00000000 b3:0a 11385      /usr/lib/libethumb_client.so.1.7.99
b6daf000-b6db6000 ---p 00008000 b3:0a 11385      /usr/lib/libethumb_client.so.1.7.99
b6db6000-b6db7000 rw-p 00007000 b3:0a 11385      /usr/lib/libethumb_client.so.1.7.99
b6db7000-b6dc0000 r-xp 00000000 b3:0a 11367      /usr/lib/libedbus.so.1.7.99
b6dc0000-b6dc7000 ---p 00009000 b3:0a 11367      /usr/lib/libedbus.so.1.7.99
b6dc7000-b6dc8000 rw-p 00008000 b3:0a 11367      /usr/lib/libedbus.so.1.7.99
b6dc8000-b6dca000 r-xp 00000000 b3:0a 10907      /usr/lib/libefreet_trash.so.1.7.99
b6dca000-b6dd1000 ---p 00002000 b3:0a 10907      /usr/lib/libefreet_trash.so.1.7.99
b6dd1000-b6dd2000 rw-p 00001000 b3:0a 10907      /usr/lib/libefreet_trash.so.1.7.99
b6dd2000-b6dd6000 r-xp 00000000 b3:0a 10905      /usr/lib/libefreet_mime.so.1.7.99
b6dd6000-b6dde000 ---p 00004000 b3:0a 10905      /usr/lib/libefreet_mime.so.1.7.99
b6dde000-b6ddf000 rw-p 00004000 b3:0a 10905      /usr/lib/libefreet_mime.so.1.7.99
b6ddf000-b6df5000 r-xp 00000000 b3:0a 10903      /usr/lib/libefreet.so.1.7.99
b6df5000-b6dfc000 ---p 00016000 b3:0a 10903      /usr/lib/libefreet.so.1.7.99
b6dfc000-b6dfd000 rw-p 00015000 b3:0a 10903      /usr/lib/libefreet.so.1.7.99
b6dfd000-b6dfe000 rw-p 00000000 00:00 0 
b6dfe000-b6e06000 r-xp 00000000 b3:0a 10892      /usr/lib/libecore_file.so.1.7.99
b6e06000-b6e07000 rw-p 00008000 b3:0a 10892      /usr/lib/libecore_file.so.1.7.99
b6e07000-b6e19000 r-xp 00000000 b3:0a 8000       /usr/lib/libeet.so.1.7.99
b6e19000-b6e20000 ---p 00012000 b3:0a 8000       /usr/lib/libeet.so.1.7.99
b6e20000-b6e21000 rw-p 00011000 b3:0a 8000       /usr/lib/libeet.so.1.7.99
b6e21000-b6f4a000 r-xp 00000000 b3:0a 11400      /usr/lib/libelementary.so.1.7.99
b6f4a000-b6f51000 ---p 00129000 b3:0a 11400      /usr/lib/libelementary.so.1.7.99
b6f51000-b6f59000 rw-p 00128000 b3:0a 11400      /usr/lib/libelementary.so.1.7.99
b6f59000-b6f5f000 rw-p 00000000 00:00 0 
b6f5f000-b6f64000 r-xp 00000000 b3:0a 12429      /usr/lib/libappcore-efl.so.1.1
b6f64000-b6f6b000 ---p 00005000 b3:0a 12429      /usr/lib/libappcore-efl.so.1.1
b6f6b000-b6f6c000 rw-p 00004000 b3:0a 12429      /usr/lib/libappcore-efl.so.1.1
b6f6c000-b6f70000 r-xp 00000000 b3:0a 10302      /usr/lib/libsys-assert.so
b6f70000-b6f77000 ---p 00004000 b3:0a 10302      /usr/lib/libsys-assert.so
b6f77000-b6f78000 rw-p 00003000 b3:0a 10302      /usr/lib/libsys-assert.so
b6f78000-b6f95000 r-xp 00000000 b3:0a 3223       /lib/ld-2.13.so
b6f95000-b6f9c000 rw-p 00000000 00:00 0 
b6f9c000-b6f9d000 r--p 0001c000 b3:0a 3223       /lib/ld-2.13.so
b6f9d000-b6f9e000 rw-p 0001d000 b3:0a 3223       /lib/ld-2.13.so
bedc3000-bede4000 rwxp 00000000 00:00 0          [stack]
ffff0000-ffff1000 r-xp 00000000 00:00 0          [vectors]
ffff0000-ffff1000 r-xp 00000000 00:00 0          [vectors]

```

