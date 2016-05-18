#Starting WiFi scanning

Works on both NX1 and NX500

In order to start wifi scan one needs to write following byte sequence to 

  - file: **/tmp/var/run/memory/ap_setting/request_type**
  - bytes: **0x2900000001000000**

For example, with poker tool ([source](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/poker.c) and [binary](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/poker.c)) on the SD card:
```
/mnt/mmc/poker /tmp/var/run/memory/ap_setting/request_type 0x0:2900000001000000
```
