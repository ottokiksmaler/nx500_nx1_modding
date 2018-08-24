# Working with focus

Working with focus is spread across few different st commands but most of it can be gathered from **st cap iq af**, for example:
  - Getting current focus position
```
[root@drime5 ~]# st cap iq af pos
fcs_pos : 971 fcs_pos_test : 971
```
  - Moving focus position (type 255 works, amount 100 (can be negative), speed 1 slowest - 255 fastest) 
```
[root@drime5 ~]# st cap iq af mv 255 100 2
cur_pos 971 tar_pos 1071
[root@drime5 ~]# st cap iq af pos         
fcs_pos : 1074 fcs_pos_test : 1074
```
  - There is even a table of noise generated (for video?)
```
[root@drime5 ~]# st cap iq af info lensspd
Index Speed Noise
    0     0    27
    1     1    27
    2     2    27
    3     3    27
    4     4    26
...
   58    58    37
   59    59    37
   60    60    37
   61   255    37
```
  - **afsta** i **afstop** start and stop auto focus
  - If your lens has limiter you can try **st cap iq af lenslimit**
  - With **st cap iq af area** and **st cap iq af area2** you can control the AF area when in suitable mode
  - Commands 120fps, sv, tv, evc, etc - I don't know yet what they do
  - To toggle AF assist beam use **st cap iq af led**
  - You can also enable debugging (not usable to me might be to someone else)
    - multi perflog [on,off] :: enable performance log
    - multi aflog [on,off] :: enable AF operation log
    - multi hybridlog [on,off] :: enable hybrid AF operation log
    - multi algo log [on,off] :: enable multi box operation log
    - multi algo save [on,off] :: save gathered multi box information
    - multi algo config [stop] [change wait] :: set wait count for small area change
    - multi algo group [samples] [areas] :: set max number of groups
    - multi algo set [id] [range] [low] [hi] :: set time-average algorithm configuration
