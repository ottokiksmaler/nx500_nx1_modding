#Shutter Count and Power-on Count

From telnet session execute **prefman get 3 0x208 l** (that's lower L, not 1):
```
[root@drime5 ~]# prefman get 3 0x208 l
[sysrw] in memory: 

 value = 4002 (0x00000fa2) 
```
Notice: this only saves shutter counts on clean power off - anything that crashes the camera will not update it.

Number of power-on events:
```
[root@drime5 ~]# prefman get 3 0x244 l               
[sysrw] in memory: 


 value = 1135 (0x0000046f) 
```
