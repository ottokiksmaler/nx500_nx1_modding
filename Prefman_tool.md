#Prefman tool

Samsung includes very powerful tool named **prefman** with modern NX cameras (/usr/bin/prefman). This tool enables a variety of operations to be performed on camera settings. There is also a **prefman.sh** script (/usr/bin/prefman.sh) that automates full dumps/restores.

Example output of prefman.sh
```
[root@drime5 ~]# prefman.sh 
+ IMG_PATH=/opt/pref
+ PREF_DEFAULT=/pref.bin
+ PREF_DEFAULT_APP=/pref_app.bin
+ PREF_DEFAULT_APP_RESTORE=/pref_app_restore.bin
+ PREF_DEFAULT_LINE=/pref_line.bin
+ PREF_DEFAULT_SYSRW=/pref_sysrw.bin
+ PREF_DEFAULT_SYS=/pref_adj_sys.bin
+ PREF_DEFAULT_CAP=/pref_adj_cap.bin
+ PREF_DEFAULT_IQ=/pref_adj_iq.bin
+ PREF_DEFAULT_VFPN=/pref_adj_vfpn.bin
+ PREF_DEFAULT_CS=/pref_adj_cs.bin
+ PREF_DEFAULT_DPC=/pref_adj_dpc.bin
+ PREF_DEFAULT_DPC2=/pref_adj_dpc2.bin
+ '[' 0 -lt 1 ']'
+ usage
+ cat

Usage: prefman.sh {COMMAND}  [ARGS..]
+ cat

Utility of preference manager.

Commands:
    --start        Inititalize and load all preference data.
    --stop         Unload and deinitialize all preference data.

+ exit 0
```

Example output of prefman (with no parameters):
```
[root@drime5 ~]# prefman
Usage: prefman {Command} [ARGS..] 

Preference manager utility. 

Preference IDs:  
   0 : app 
   1 : app_restore 
   2 : line 
   3 : sysrw 
   4 : adj_sys 
   5 : adj_cap 
   6 : adj_iq 
   7 : adj_vfpn 
   8 : adj_cs 
   9 : adj_dpc 
   10 : adj_dpc2 

Commands: 
 load       {ID...}  NAND) Load preference data with 'ID' to memory from mtd 
                     EMMC) Load preference data with 'ID' to memory from node(emmc)
 save       {ID...}  NAND) Save preference data with 'ID' to mtd from memory 
                     EMMC) Save preference data with 'ID' to USING partition of emmc from memory 
 fetch      {ID...}  EMMC) Fetch raw preference data to image file from storage node.
 store      {ID...}  EMMC) Store raw preference data to storage node from image file.
 reset      {ID...}  NAND) Reset preference data to default with 'ID' to memory from mtd 
                     EMMC) Reset preference data to default with 'ID' to memory from USING partition of emmc 
                     If 'ID' isn't given, reset all existing preference data 

 dump       [ID]     Dump preference data in memory with hex format into stdout. 
 info       [ID]     Show offset information for preference into stdout. 

 get        [ID] [offset] [type]          Get data at offset in memory. 
 set        [ID] [offset] [type] [value]  Set data at offset in memory. 
 set_string [ID] [offset] [value]         Set string data at offset in memory. 
 get_string [ID] [offset] [Length]        Get string data at offset in memory. 
 addr       [ID] {offset} {type} {value}  Get addr corresponding to pref data and set in memory. 

 load_file  [ID] [file]  Load preference data with 'ID' to memory from the file 
 save_file  [ID] [file]  Save preference data with 'ID' to mtd to the file 
```

To get individual settings use **prefman get**:
```
[root@drime5 ~]# prefman get   
Usage: prefman get [ID] [offset] [type] 

[ID]: preference id 
[offset]: Use 'prefman info [ID] 
[type]: 
  b: byte 
  s: short 
  l: long 
  v=len: variable length 
```

To find out what is contained in each of the "stores", use pref info ID, like this for SYSRW:
```
[root@drime5 ~]# prefman info 3

------------------------------------------------
     Offset    Size    Name    [sysrw] 
------------------------------------------------
 0x00000200    0004    SYSRWPREF_DCF_SEED 
 0x00000204    0004    SYSRWPREF_DU_SHUTTER_COUNT 
 0x00000208    0004    SYSRWPREF_SHUTTER_COUNT
 0x0000020c    0004    SYSRWPREF_SHUTTER_COMPENSATION_TIME 
 0x00000210    0040    SYSRWPREF_SHUTTER_COMPENSATION_BUFFER 
 0x00000238    0004    SYSRWPREF_SHUTTER_COMPENSATION_BUFFER_SIZE 
 0x0000023c    0004    SYSRWPREF_SHUTTER_ERR81_COUNT 
 0x00000240    0004    SYSRWPREF_SHUTTER_ERR91_COUNT 
 0x00000244    0004    SYSRWPREF_POWER_ON_COUNT 
 0x00000248    0004    SYSRWPREF_FLASH_INT_COUNT 
 0x0000024c    0004    SYSRWPREF_FLASH_EXT_COUNT 
```

Interesting name at **0x0208** - **SYSRWPREF_SHUTTER_COUNT**. So, to get the number of times a shutter has been used (and camera was powered off without crashing, freezing, soft-rebooting, etc - this value is updated only on clean shutdown):
```
[root@drime5 ~]# prefman get 3 0x208 l
[sysrw] in memory: 

 value = 4002 (0x00000fa2) 
```

For example, to disable REC limit without going into DEV Mode, do:
```
[root@drime5 ~]# prefman info 0|grep LIMIT
 0x0000c2d9    0004    APPPREF_B_DISABLE_MOVIE_REC_LIMIT 

[root@drime5 ~]# prefman get 0 0x0c2d9 l  
[app] in memory: 
 value = 0 (0x00000000) 

[root@drime5 ~]# prefman set 0 0x0c2d9 l 1
[app] in memory: 
value = 1 (0x00000001) 
```
That's it. No more recording limit.

There are plenty of options, it will take some time to explore.
