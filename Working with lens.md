#Working with lens

Most of the work with lens is handled by **st cap lens** command. 

Some of the most usable subcommands are:
  - log - can set logging level (including rxtx - 5)
  - general - general information including supported features
  - sdget - lens specific data - a lot of very detailed information about the lens
  - zoom - current zoom position
  - focus_pos - current focus position
  - focus near|far - focus to mfd or infinity
  - status - lens status - not working? Have to reboot the camera afterwards.
  - spi - can set spi mode (for debugging and developing?)
  - af - focus data
  - getrange - range of focus and aperture
  - lensinfo, lensproperty - additional operational lens data
  - ifn, ifn_en - iFn functions

Sample output for 16-50PZ lens for various commands:
```
[root@drime5 ~]# st cap lens            
usage:  st cap lens [command] [param]
        * command list *
        [attatch]       set attatch flags
        [rport] read ports
        [log]   Lens debug log level set
        [general]       Show Lens general info
        [sdget] Show Lens Specific Data
        [pdget] Show Lens Property Data
        [zoom]  current zoom point Data
        [alt_iris]      Iris moving test
        [oper_iris]     Iris operation test
        [alt_focus]     Focus moving test
        [oper_focus]    Focus operation test
        [focus_pos]     Show current focus position
        [wport] write ports
        [fwupdate]      update lens fw 
        [power] power on, off 
        [polling]       start,stop polling rb,mount 
        [focus] [near | far]    focus move to near or far
        [status]        Show status of DET, RB, Current state, NextState, Eventflag 
        [wreg]  write spi [Lens to Body] 
        [spi]   select spi mode 
        [3d]    check 3D mode and 3D lens position
        [3dmode]        3d status and SW information
        [rb]    RB status 
        [trace] display communicate trace
        [sync]  sync signal on/off
        [info]  display Lens Information
        [af]    display af area Information
        [getrange]      display focus range and iris range
        [trace]
        [sync]
        [info]
        [type]
        [3dlo]
        [3dro]
        [state]
        [cmd]
        [vf_on]
        [adj_awb]
        [range]
        [vf_on]
        [vf_on]
        [lensinfo]      lens information 
        [lensproperty]  lens property information
        [reset] lens reset command
        [dis_tmout]     lens state time out disable
        [lensversion]   lens version check in sd card and body
        [ifn] [on | off]        ifn function on / off
        [ifn_en] [6]    ifn_enable degree 6
        [op_supp] [op code]     check operation support
        [ctti]  send test change_tracking_target_info op
[root@drime5 ~]# st cap lens log
        [backlash]      get lens backlashnusage:        st cap lens log [param]
                * param list *
                [rxtx]
                        - level 5
                [x]
                        - level x
[root@drime5 ~]# st cap lens general

 === GetUnitInfo =================================
 StandardVer = 100
 NumOfOperation = 14, NumOfEvent = 5, NumOfProperty = 14, NumOfSpecificData = 30, m_wAdjustExecution = f
 OperationSupport -> 
0x1001 0x1005 0x1006 0x1007 0x1008 0x1009 0x100c 0x100d 0x1101 0x1102 0x110b 0x1103 0x1104 0x1109 
 EventSupport -> 
0x4001, 0x4002, 0x4003, 0x4004, 0x4006, 
 PropertySupport -> 
0x5001, 0x5002, 0x5003, 0x5007, 0x5008, 0x5009, 0x500a, 0x500c, 0x500d, 0x500e, 0x5010, 0x5011, 0x5013, 0x5014, 
 SpecificDataSupport -> 
0x6001, 0x6002, 0x6003, 0x6004, 0x6005, 0x6006, 0x6007, 0x6008, 0x6009, 0x600a, 0x600b, 0x600c, 0x600d, 0x600e, 0x600f, 0x6010, 0x6011, 0x6012, 0x6013, 0x6014, 0x6016, 0x6017, 0x6018, 0x601a, 0x601b, 0x6019, 0x601c, 0x601d, 0x6024, 0x6025, 
 StatusSupport -> 
0x7001, 0x7002, 0x7003, 0x7004, 
 Manufacturer -> SAMSUNG??NX 16-50mm F3.5-5.6 Power Zoom
 Model -> XL1401
 DeviceVer -> 01.30_01.50
 SerialNum -> 609901768820
 === GetUnitInfo ================================= 
[root@drime5 ~]# st cap lens sdget  

 [Specific eLENS_SPECIFIC_LENS_ID Data iRet = 8194, Length = 2]
 === SpecificData =================================
 SpecificCode = 0x6001
 NumOfData = 1, Format= 0x4
 Data = 15      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_LENS_TYPE Data iRet = 8194, Length = 20]
 === SpecificData =================================
 SpecificCode = 0x6002
 NumOfData = 20, Format= 0x4002
 Data = 1       0       1       1       1       31      1       0       3       0       0       1       0       29      15      1       5       0       0       0       
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_COMMUNICATION_CLOCK Data iRet = 8194, Length = 4]
 === SpecificData =================================
 SpecificCode = 0x6003
 NumOfData = 2, Format= 0x4004
 Data = 250     2000    
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_FOCUSING_SPEED Data iRet = 8194, Length = 124]
 === SpecificData =================================
 SpecificCode = 0x6004
 NumOfData = 62, Format= 0x4004
 Data = 27      283     539     795     1050    1306    1563    1819    2075    2331    2587    2843    3099    3357    3613    3869    4125    4381    4637    4893    5149    5406    5662    5918    6174    6432    6688    6944    7200    7456    7712    7969    8225    8481    8738    8994    9250    9506    9762    10018   10274   10531   10787   11043   11299   11555   11811   12067   12323   12579   12835   13093   13349   13605   13861   14117   14373   14629   14885   15141   15397   65317   
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_AFINF_POSITION Data iRet = 8194, Length = 36]
 === SpecificData =================================
 SpecificCode = 0x6005
 NumOfData = 18, Format= 0x4004
 Data = 971     1056    1222    1402    1538    1650    1764    1888    1998    2139    2303    2482    2644    2829    3036    3236    3474    3731    
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_ANINF_POSITION_TEMP Data iRet = 8194, Length = 54]
 === SpecificData =================================
 SpecificCode = 0x6006
 NumOfData = 54, Format= 0x4001
 Data = 253     255     2       248     253     6       248     252     6       247     252     6       247     252     7       246     252     7       246     252     7       245     251     8       245     251     8       244     251     9       243     251     9       243     250     10      242     250     10      241     250     11      240     249     11      240     249     12      239     249     12      238     248     13      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_FOCUSING_AMOUNT Data iRet = 8194, Length = 36]
 === SpecificData =================================
 SpecificCode = 0x6007
 NumOfData = 18, Format= 0x4004
 Data = 232     202     223     246     266     286     309     335     366     401     445     493     543     600     668     741     827     877     
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_AFNEAREST_MECHA_LIMIT Data iRet = 8194, Length = 36]
 === SpecificData =================================
 SpecificCode = 0x6008
 NumOfData = 18, Format= 0x4004
 Data = 1784    1905    2095    2303    2466    2614    2747    2879    3030    3212    3428    3654    3881    4131    4407    4694    5032    5121    
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_FOCUS_PATICULAR_ATTRIBUTE Data iRet = 8194, Length = 7]
 === SpecificData =================================
 SpecificCode = 0x6009
 NumOfData = 7, Format= 0x4002
 Data = 80      1       80      6       6       6       6       
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_FOCUS_BACKLASH Data iRet = 8194, Length = 1]
 === SpecificData =================================
 SpecificCode = 0x600a
 NumOfData = 1, Format= 0x2
 Data = 4       
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_IRIS_SPEED Data iRet = 8194, Length = 20]
 === SpecificData =================================
 SpecificCode = 0x600b
 NumOfData = 10, Format= 0x4004
 Data = 28      7196    6172    5148    4124    3107    2088    1074    567     65341   
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_ACTUAL_FOCAL_LENGTH Data iRet = 8194, Length = 36]
 === SpecificData =================================
 SpecificCode = 0x600c
 NumOfData = 18, Format= 0x4004
 Data = 330     343     366     392     418     447     478     512     548     585     627     671     717     766     821     878     938     970     
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_NOMINAL_FOCAL_LENGTH Data iRet = 8194, Length = 36]
 === SpecificData =================================
 SpecificCode = 0x600d
 NumOfData = 18, Format= 0x4004
 Data = 320     340     360     380     420     440     480     520     560     600     640     680     740     780     840     900     960     1000    
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_WIDE_ACTUAL_F_NUMBER Data iRet = 8194, Length = 24]
 === SpecificData =================================
 SpecificCode = 0x600e
 NumOfData = 24, Format= 0x4002
 Data = 58      60      61      63      66      68      70      73      75      79      81      84      86      89      92      94      98      102     107     112     118     123     130     136     
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_OPEN_ACTUAL_F_NUMBER Data iRet = 8194, Length = 18]
 === SpecificData =================================
 SpecificCode = 0x600f
 NumOfData = 18, Format= 0x4002
 Data = 59      60      61      63      64      65      67      68      69      71      72      74      75      77      78      80      81      82      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_NORMINAL_F_NUMBER Data iRet = 8194, Length = 3]
 === SpecificData =================================
 SpecificCode = 0x6010
 NumOfData = 3, Format= 0x4002
 Data = 58      144     80      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_OIS_COMPENSATION_ABILITY Data iRet = 8194, Length = 18]
 === SpecificData =================================
 SpecificCode = 0x6011
 NumOfData = 18, Format= 0x4002
 Data = 16      16      16      16      16      16      16      16      16      16      16      16      16      16      16      16      16      16      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_K_VALUE Data iRet = 8194, Length = 360]
 === SpecificData =================================
 SpecificCode = 0x6012
 NumOfData = 180, Format= 0x4004
 Data = 115     114     114     114     114     114     113     113     113     112     116     116     115     115     115     115     115     115     114     113     118     118     118     118     118     117     117     117     117     116     122     121     121     121     121     120     120     120     120     119     126     126     126     126     125     125     125     125     124     123     133     133     133     132     132     132     131     131     131     130     140     140     140     139     139     139     138     138     138     137     148     148     147     147     147     146     146     145     145     144     155     155     155     155     154     154     153     153     152     152     162     161     161     161     160     160     159     159     158     157     168     168     167     167     167     166     166     165     164     163     175     175     174     174     173     173     172     171     171     170     182     182     181     181     180     179     179     178     177     176     189     189     188     188     187     186     186     185     184     183     197     197     196     196     195     194     193     193     192     190     205     205     204     203     203     202     201     200     199     198     212     212     211     210     210     209     208     207     206     204     215     215     214     214     213     212     211     210     209     207     
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_D_VALUE Data iRet = 8194, Length = 144]
 === SpecificData =================================
 SpecificCode = 0x6013
 NumOfData = 36, Format= 0x4006
 Data = 67      37713   66      40180   66      44807   65      50062   66      54679   66      59519   67      64608   68      70195   69      76601   70      83862   71      92598   72      102162  73      112026  75      123038  77      135680  79      149065  81      164389  82      173317  
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_DELTA_IB Data iRet = 8194, Length = 720]
 === SpecificData =================================
 SpecificCode = 0x6014
 NumOfData = 360, Format= 0x4003
 Data = -1      0       -1      0       -2      1       -2      2       -3      3       -3      4       -3      5       -4      6       -4      9       -5      13      -1      -1      -1      0       -2      0       -2      1       -2      2       -3      3       -3      3       -4      4       -4      5       -4      9       -1      -1      -1      -1      -2      -1      -2      0       -2      1       -3      1       -3      2       -4      3       -4      4       -4      6       -1      -2      -1      -2      -3      -2      -3      -1      -2      0       -3      0       -3      1       -3      3       -4      3       -4      4       -2      -3      -3      -3      -3      -3      -4      -2      -4      -2      -3      -1      -5      0       -4      1       -5      2       -6      3       -3      -4      -3      -3      -3      -3      -4      -3      -4      -2      -4      -2      -5      -1      -5      -1      -5      0       -4      1       -4      -5      -5      -4      -4      -3      -5      -4      -6      -3      -6      -3      -5      -2      -6      -2      -6      -1      -6      0       -5      -4      -5      -4      -5      -3      -6      -4      -6      -4      -6      -3      -6      -3      -5      -2      -6      -2      -6      -2      -6      -5      -6      -4      -5      -4      -5      -4      -6      -4      -6      -4      -6      -4      -6      -3      -6      -3      -7      -2      -6      -5      -6      -4      -6      -4      -5      -4      -6      -4      -6      -4      -6      -4      -6      -3      -6      -2      -7      -2      -7      -5      -7      -5      -7      -5      -6      -5      -7      -4      -7      -4      -7      -4      -7      -3      -7      -3      -7      -2      -7      -5      -7      -6      -7      -6      -7      -6      -6      -6      -7      -5      -7      -4      -7      -3      -7      -2      -7      -1      -7      -6      -7      -6      -7      -6      -7      -6      -6      -5      -7      -5      -7      -4      -7      -3      -7      -2      -7      -1      -7      -6      -7      -6      -6      -6      -1      -6      -6      -5      -6      -4      -7      -3      -7      -3      -7      -2      -7      0       -6      -6      -6      -6      -6      -5      -6      -5      -6      -5      -6      -4      -7      -3      -6      -1      -6      -1      -6      0       -5      -5      -5      -5      -5      -5      -5      -5      -5      -4      -5      -3      -4      -2      -4      -1      -3      1       -3      2       -5      -4      -5      -3      -4      -4      -4      -3      -3      -3      -2      -1      -2      0       -1      2       0       3       1       4       -5      -3      -5      -3      -4      -3      -4      -2      -3      -1      -2      1       -1      1       0       3       1       5       2       4       
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_DELTA_IB_OFFSET Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6015
 0x6015 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_T_NUMBER Data iRet = 8194, Length = 1]
 === SpecificData =================================
 SpecificCode = 0x6016
 NumOfData = 1, Format= 0x2
 Data = 90      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_EXT_PUPIL_POSITION Data iRet = 8194, Length = 36]
 === SpecificData =================================
 SpecificCode = 0x6017
 NumOfData = 18, Format= 0x4004
 Data = 661     670     689     717     755     806     857     909     959     998     1037    1078    1119    1162    1209    1255    1298    1319    [ 1: 1020.794201] I/DP           (A7 47): Live: >># frame: 15303, elapsed t:0h 17m 0s(1020053ms), 15.002fps, 0xbba6bc00                                                                                                                 

 === SpecificData =================================

 [Specific eLENS_SPECIFIC_IMAGE_CIRCLE Data iRet = 8194, Length = 6]
 === SpecificData =================================
 SpecificCode = 0x6018
 NumOfData = 3, Format= 0x4
 Data = 1560    2350    2850    
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_RELATIVE_ILLUMINANCE Data iRet = 8194, Length = 360]
 === SpecificData =================================
 SpecificCode = 0x6019
 NumOfData = 180, Format= 0x4004
 Data = 2005    1817    1468    1290    1112    897     631     99      77      75      2011    1823    1477    1296    1116    950     721     97      81      79      2005    1831    1487    1309    1137    973     815     102     86      82      2007    1843    1507    1327    1151    987     836     102     85      82      2017    1864    1536    1356    1186    1020    868     101     83      80      2021    1874    1561    1386    1221    1053    907     99      80      75      2019    1886    1583    1411    1249    1100    950     97      75      72      2028    1903    1610    1452    1294    1139    989     94      71      69      2015    1905    1628    1468    1315    1171    985     98      78      63      2017    1909    1634    1487    1339    1198    971     101     82      63      2028    1913    1651    1503    1362    1219    977     103     84      62      2021    1911    1661    1516    1384    1241    985     102     83      62      2025    1919    1675    1536    1405    1266    995     102     84      62      2034    1917    1694    1563    1427    1290    1012    102     83      60      2015    1892    1690    1567    1436    1309    1026    101     80      57      2005    1882    1696    1577    1452    1329    1055    98      77      52      1985    1870    1694    1587    1464    1348    1075    97      75      49      1970    1858    1702    1587    1477    1356    1079    96      75      48      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_DISTORTION Data iRet = 8194, Length = 216]
 === SpecificData =================================
 SpecificCode = 0x601a
 NumOfData = 54, Format= 0x4005
 Data = 10000   -3      0       10000   -3      0       10000   -2      0       10000   -2      0       10000   -1      0       10000   -1      0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       10000   0       0       
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_LATERAL_CHROMATIC_ABERRATION Data iRet = 8194, Length = 144]
 === SpecificData =================================
 SpecificCode = 0x601b
 NumOfData = 36, Format= 0x4005
 Data = 9542    -2336   9235    -2185   8585    -1845   8132    -1679   8134    -1845   8299    -2147   8254    -2276   8124    -2339   7828    -2270   7256    -1965   6522    -1540   5800    -1130   5145    -780    4482    -503    3805    1670    3126    665     2297    1113    1814    1432    
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_COLOR_CONTRIBUTION Data iRet = 8194, Length = 16]
 === SpecificData =================================
 SpecificCode = 0x601c
 NumOfData = 8, Format= 0x4004
 Data = 3532    4096    2129    3508    4096    2278    1       0       
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_DELTA_IB_F Data iRet = 8194, Length = 1440]
 === SpecificData =================================
 SpecificCode = 0x601d
 NumOfData = 720, Format= 0x4003
 Data = 9       9       0       1       10      9       0       1       10      10      1       0       10      10      1       0       11      10      1       0       12      11      2       0       12      11      2       -1      13      12      3       -1      14      13      2       -2      14      13      3       -4      10      9       0       0       10      9       0       0       10      10      -1      0       11      10      0       -1      10      10      -1      -1      12      11      1       -1      12      11      0       -1      12      12      1       -1      13      12      0       -2      13      13      1       -4      9       9       -2      -1      9       9       -3      -1      9       9       -2      -1      10      10      -1      -1      11      10      -1      -1      11      10      -3      -2      11      11      0       -2      13      11      -1      -2      13      12      -1      -2      13      12      0       -4      8       8       -4      -2      7       8       -4      -2      8       8       -4      -2      8       9       -3      -2      9       9       -4      -3      10      10      -3      -3      10      10      -3      -3      10      10      -2      -4      12      11      -2      -3      12      12      -4      -5      5       6       -8      -4      5       6       -6      -4      6       6       -7      -4      6       7       -5      -4      7       7       -6      -4      8       8       -6      -5      8       8       -5      -5      8       9       -6      -5      9       9       -6      -5      10      10      -6      -6      3       4       -10     -6      3       4       -8      -6      4       4       -10     -6      4       5       -10     -6      4       5       -8      -7      5       6       -9      -6      6       6       -9      -7      7       7       -9      -7      7       7       -8      -7      7       8       -8      -8      1       2       -12     -7      2       2       -11     -7      2       3       -9      -7      2       3       -11     -7      2       4       -9      -7      3       4       -10     -7      3       5       -9      -7      5       5       -9      -7      6       6       -8      -7      5       6       -9      -7      0       1       -12     -6      0       1       -10     -6      0       2       -11     -6      0       2       -10     -6      0       2       -10     -6      3       3       -9      -6      2       3       -10     -6      3       4       -7      -6      3       5       -8      -6      4       5       -9      -6      -2      0       -10     -6      -2      0       -11     -6      -1      1       -10     -6      -2      1       -9      -5      0       1       -9      -5      1       2       -8      -5      1       2       -9      -5      3       3       -7      -4      4       4       -7      -4      3       4       -7      -4      -2      -1      -9      -5      -3      0       -9      -5      -3      0       -9      -4      -1      1       -9      -4      0       1       -9      -4      1       2       -7      -4      0       2       -7      -3      2       3       -7      -3      2       4       -6      -3      3       4       -6      -3      -3      -1      -8      -3      -3      -1      -8      -3      -3      0       -7      -3      -2      0       -7      -2      -2      1       -8      -2      0       1       -8      -2      0       2       -6      -2      0       3       -6      -2      2       3       -6      -2      3       4       -4      -2      -3      -1      -7      -2      -4      -1      -7      -2      -3      -1      -6      -2      -3      0       -7      -1      -2      0       -6      -1      0       1       -5      -1      1       2       -5      -1      0       3       -4      -1      1       3       -4      -2      2       4       -3      -2      -4      -2      -9      -2      -4      -2      -8      -1      -3      -1      -6      -1      -3      0       -6      -1      -2      0       -6      -1      -1      1       -5      -1      0       2       -5      -1      0       2       -4      -1      2       3       -5      -2      1       4       -4      -2      -3      -2      -8      -2      -4      -2      -8      -2      -4      -1      -7      -1      -2      -1      -9      -1      -1      0       -7      -1      0       1       -5      -1      1       2       -5      -2      2       3       -5      -2      2       4       -4      -2      2       4       -3      -2      -4      -2      -8      -2      -3      -2      -7      -2      -4      -1      -7      -2      -2      0       -6      -2      -2      0       -7      -2      0       1       -6      -2      2       3       -4      -3      2       3       -4      -3      4       4       -3      -2      4       5       -5      -3      -2      -1      -8      -3      -1      -1      -9      -3      -1      0       -7      -2      -1      1       -8      -3      1       1       -8      -3      3       3       -6      -3      3       3       -5      -3      6       4       -4      -4      6       5       -5      -3      6       5       -3      -3      0       0       -8      -4      3       1       -7      -4      3       1       -6      -4      3       2       -8      -4      5       3       -6      -4      7       3       -5      -4      8       4       -5      -5      10      4       -2      -4      10      5       -3      -3      13      5       -2      -3      3       1       -7      -5      4       1       -7      -4      4       2       -7      -4      7       3       -5      -4      8       3       -5      -4      10      3       -3      -4      11      4       -2      -4      12      4       -2      -3      14      5       -1      -3      15      5       -2      -2      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_DELTA_AVCOEFF Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x601e
 0x601e : I don't have info about this code 
 [Specific eLENS_SPECIFIC_FALSE_IRIS_COEFF Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x601f
 0x601f : I don't have info about this code 
 [Specific eLENS_SPECIFIC_WIDE_ACTUAL_FNUMBER_FI Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6020
 0x6020 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_OPEN_ACTUAL_FNUMBER_FI Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6021
 0x6021 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_FOCUS_RANGE_INFO Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6022
 0x6022 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_FOCUS_LIMIT_INFO Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6023
 0x6023 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_EXT_PUPIL_POSITION_DT Data iRet = 8194, Length = 108]
 === SpecificData =================================
 SpecificCode = 0x6024
 NumOfData = 54, Format= 0x4004
 Data = 3303    3282    3257    3349    3328    3306    3446    3424    3399    3584    3560    3531    3774    3748    3715    4031    4004    3966    4284    4255    4210    4545    4514    4462    4793    4759    4699    4991    4952    4884    5187    5143    5065    5390    5341    5251    5594    5539    5437    5810    5748    5631    6047    5975    5840    6274    6193    6037    6488    6394    6214    6595    6492    6299    
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_RAY_ANGLE_EXT_PUPIL Data iRet = 8194, Length = 2740]
 === SpecificData =================================
 SpecificCode = 0x6025
 NumOfData = 2740, Format= 0x4002
 Data = 180     10      0       0       232     33      0       0       0       0       0       0       63      0       87      0       0       0       1       0       2       0       0       0       1       0       0       0       0       0       0       0       2       0       3       0       4       0       0       0       3       0       5       0       6       0       0       0       4       0       0       0       0       0       1       0       5       0       0       0       0       0       255     0       6       0       7       0       8       0       0       0       7       0       9       0       10      0       0       0       8       0       0       0       0       0       2       0       9       0       0       0       0       0       254     0       10      0       11      0       12      0       0       0       11      0       13      0       14      0       0       0       12      0       15      0       16      0       0       0       13      0       0       0       0       0       3       0       14      0       0       0       0       0       253     0       15      0       17      0       18      0       0       0       16      0       19      0       20      0       0       0       17      0       21      0       22      0       0       0       18      0       25      0       26      0       0       0       19      0       23      0       24      0       0       0       20      0       27      0       28      0       0       0       21      0       29      0       30      0       0       0       22      0       0       0       0       0       4       0       23      0       39      0       40      0       0       0       24      0       37      0       38      0       0       0       25      0       35      0       36      0       0       0       26      0       33      0       34      0       0       0       27      0       31      0       32      0       0       0       28      0       41      0       42      0       0       0       29      0       43      0       44      0       0       0       30      0       0       0       0       0       244     0       31      0       0       0       0       0       8       0       32      0       0       0       0       0       222     0       33      0       61      0       62      0       0       0       34      0       59      0       60      0       0       0       35      0       57      0       58      0       0       0       36      0       55      0       56      0       0       0       37      0       53      0       54      0       0       0       38      0       51      0       52      0       0       0       39      0       49      0       50      0       0       0       40      0       47      0       48      0       0       0       41      0       45      0       46      0       0       0       42      0       0       0       0       0       5       0       43      0       0       0       0       0       221     0       44      0       63      0       64      0       0       0       45      0       0       0       0       0       80      0       46      0       0       0       0       0       234     0       47      0       0       0       0       0       239     0       48      0       0       0       0       0       248     0       49      0       0       0       0       0       223     0       50      0       0       0       0       0       211     0       51      0       0       0       0       0       252     0       52      0       0       0       0       0       251     0       53      0       85      0       86      0       0       0       54      0       83      0       84      0       0       0       55      0       81      0       82      0       0       0       56      0       79      0       80      0       0       0       57      0       77      0       78      0       0       0       58      0       75      0       76      0       0       0       59      0       73      0       74      0       0       0       60      0       71      0       72      0       0       0       61      0       69      0       70      0       0       0       62      0       67      0       68      0       0       0       63      0       65      0       66      0       0       0       64      0       0       0       0       0       232     0       65      0       0       0       0       0       33      0       66      0       0       0       0       0       128     0       67      0       0       0       0       0       67      0       68      0       0       0       0       0       18      0       69      0       0       0       0       0       176     0       70      0       0       0       0       0       22      0       71      0       0       0       0       0       17      0       72      0       0       0       0       0       12      0       73      0       0       0       0       0       218     0       74      0       0       0       0       0       212     0       75      0       0       0       0       0       224     0       76      0       0       0       0       0       226     0       77      0       0       0       0       0       9       0       78      0       0       0       0       0       213     0       79      0       0       0       0       0       228     0       80      0       0       0       0       0       214     0       81      0       0       0       0       0       230     0       82      0       0       0       0       0       7       0       83      0       0       0       0       0       220     0       84      0       0       0       0       0       247     0       85      0       0       0       0       0       249     0       86      0       0       0       0       0       10      0       43      14      176     133     97      107     104     11      235     42      202     178     173     177     94      10      252     84      5       124     86      196     175     128     5       125     173     154     250     0       174     85      189     92      128     21      141     111     214     32      10      231     94      87      48      10      193     88      43      1       0       6       32      196     24      0       9       156     33      94      214     229     112     78      1       98      0       67      201     12      64      8       51      43      218     221     173     34      36      144     175     32      108     97      6       72      94      7       146     2       189     174     53      167     15      136     86      133     50      80      196     30      67      201     64      58      11      5       123     90      53      172     33      17      82      172     60      154     191     100     134     116     38      121     51      130     43      133     107     214     164     72      38      87      108     199     21      171     0       0       194     28      128     154     186     171     141     117     215     121     33      41      149     141     100     130     69      74      196     98      161     89      155     16      0       112     156     0       0       7       48      0       0       0       78      108     201     6       40      44      80      88      131     16      2       12      184     88      161     226     144     169     148     23      101     90      23      148     133     76      144     236     165     6       65      102     23      148     131     36      59      36      60      164     49      40      93      196     154     247     32      202     67      188     161     226     148     49      7       153     46      20      195     17      194     111     20      28      74      68      187     97      123     145     33      208     99      104     127     28      49      33      51      1       4       128     153     246     160     184     43      161     135     4       24      177     94      108     72      17      5       128     225     76      165     208     1       204     19      128     14      96      0       0       231     249     6       32      177     33      136     24      28      32      197     48      120     242     35      178     173     10      141     33      121     84      4       203     18      21      5       14      240     67      82      23      113     33      229     41      173     70      36      39      153     38      249     250     35      13      17      153     38      238     13      6       18      54      32      127     56      216     44      64      56      225     32      131     24      201     1       255     18      0       161     224     76      12      253     2       20      145     120     62      177     222     75      133     116     136     25      82      34      58      4       24      49      0       82      232     156     0       115     115     115     5       46      128     14      96      1       249     198     24      166     49      136     116     36      59      0       58      18      221     220     206     145     164     223     9       18      14      45      175     37      93      75      128     150     116     93      233     31      104     98      133     50      34      242     44      154     92      114     1       15      127     180     68      64      70      215     197     37      65      1       162     52      131     17      126     156     39      185     11      196     69      138     2       112     154     225     98      100     22      151     44      65      118     85      2       35      12      225     48      38      92      33      119     242     67      194     133     136     98      76      133     59      92      162     98      15      5       90      149     92      193     205     56      0       14      107     165     130     151     64      7       59      189     25      0       33      132     60      166     75      36      139     152     30      39      223     145     195     65      169     140     83      124     33      46      57      129     1       214     109     201     19      42      195     189     112     218     136     66      116     84      165     166     38      238     41      21      45      36      246     221     238     133     17      72      124     96      38      112     242     65      187     247     194     67      36      141     136     44      204     5       88      80      112     249     119     98      102     36      48      54      157     18      133     51      166     169     101     200     166     71      127     190     36      196     24      134     115     50      225     76      130     98      69      65      86      165     80      7       48      7       48      0       78      57      131     154     114     238     192     0       0       152     24      225     205     78      49      68      115     186     150     64      16      96      56      76      144     166     92      48      135     146     215     121     126     33      146     144     240     0       98      152     131     36      50      238     206     68      100     41      83      92      161     157     9       129     137     232     48      142     165     186     54      128     185     20      237     16      196     13      5       163     131     14      165     233     162     51      30      72      4       222     32      226     9       121     67      146     235     53      62      78      104     33      33      228     203     128     156     38      224     135     113     84      115     4       224     3       152     39      1       56      186     88      57      169     116     14      237     193     112     130     197     92      196     134     16      150     4       226     230     21      59      83      56      56      80      94      76      184     65      137     136     4       134     106     142     36      45      112     218     74      164     133     237     162     220     161     142     19      72      238     219     230     128     74      34      160     19      68      98      130     208     135     141     82      237     57      17      169     34      93      69      202     47      178     80      18      71      147     24      132     125     75      36      253     65      138     30      162     54      123     224     41      76      166     89      165     79      171     61      207     58      132     16      34      4       142     102     120     177     76      21      106     85      7       55      48      78      3       152     57      167     0       28      194     239     4       165     140     130     165     4       60      160     100     133     132     206     33      249     153     0       6       9       156     3       133     49      128     139     169     105     27      145     32      226     51      202     176     168     16      242     8       51      229     222     19      52      206     98      56      74      130     16      112     6       72      14      166     227     132     120     145     47      85      24      186     70      2       120     28      41      223     167     193     100     12      145     124     80      65      22      209     160     161     44      183     83      240     72      112     12      55      7       162     137     229     4       206     2       151     68      224     3       152     57      130     112     1       204     0       53      151     24      112     153     0       65      112     12      83      0       7       123     133     12      192     72      0       96      33      226     12      23      124     155     200     140     67      192     197     4       25      32      196     55      223     130     32      137     55      147     57      65      108     79      16      0       63      129     235     22      250     20      142     81      21      20      168     79      36      114     0       196     187     240     145     65      65      151     104     182     142     172     104     163     120     98      136     250     237     253     146     178     1       194     131     132     203     138     252     68      87      117     128     218     138     93      0       28      211     128     14      96      0       14      105     192     254     39      184     27      145     48      32      192     98      6       33      199     226     14      32      177     27      19      132     200     79      104     112     154     29      249     34      49      69      59      92      40      213     17      78      60      144     194     0       223     132     155     65      177     28      137     216     131     20      70      131     3       199     232     163     201     0       122     74      57      105     35      241     128     28      94      228     153     99      56      72      136     45      220     7       8       1       136     186     106     27      196     131     51      98      137     65      235     65      21      17      86      103     106     181     42      185     167     28      192     28      212     186     46      150     14      105     192     115     14      253     18      33      16      108     65      82      21      108     197     5       193     9       99      120     108     192     4       56      75      16      103     66      99      36      6       110     54      121     8       141     20      154     196     135     147     25      137     31      200     151     144     103     85      22      48      17      56      230     199     9       131     182     137     24      80      91      106     53      241     36      88      144     153     0       105     179     209     64      19      58      49      16      104     60      140     196     17      155     78      6       16      153     33      231     130     75      90      171     19      160     181     46      128     0       14      96      230     156     93      45      75      160     39      28      195     102     136     220     39      190     49      2       20      203     128     112     8       126     144     88      103     10      176     77      17      118     16      104     1       153     216     52      68      4       121     7       100     166     236     85      48      132     192     189     192     68      135     224     98      144     100     133     232     30      72      70      203     68      150     218     131     80      65      167     16      5       204     0       255     68      150     238     135     181     84      149     146     15      16      0       70      32      15      248     147     152     161     42      23      84      241     71      75      32      201     224     185     168     162     151     68      227     155     155     154     151     64      7       48      115     78      57      167     3       244     79      113     51      80      165     184     83      223     0       196     38      112     67      47      37      0       83      42      8       44      80      121     40      96      1       191     64      32      0       182     16      136     164     59      0       0       120     98      102     40      78      32      101     163     154     112     152     132     221     191     36      47      36      139     189     72      109     16      102     41      11      49      61      42      198     60      131     202     77      114     136     57      19      176     50      66      13      31      223     162     16      38      93      5       156     37      138     8       53      192     32      101     46      128     0       0       230     0       0       230     0       12      216     0       152     137     154     35      112     129     128     30      181     168     129     28      24      108     65      194     15      32      4       32      180     179     145     169     228     139     224     2       35      16      25      5       156     127     196     159     156     137     83      74      164     28      23      166     116     29      30      5       41      249     25      32      242     144     176     136     215     0       239     82      145     33      200     234     127     128     130     26      37      218     97      146     142     20      21      3       19      78      6       23      142     11      41      71      76      186     39      105     123     171     69      47      32      188     171     20      186     2       113     205     56      186     88      57      169     116     0       115     115     4       230     204     136     98      66      84      1       151     84      0       152     16      112     189     195     218     130     196     144     132     11      3       18      12      12      188     164     30      7       148     160     192     216     36      47      128     209     86      108     253     37      9       112     171     186     201     205     56      80      195     41      53      32      21      42      71      180     110     16      89      208     98      20      242     16      94      51      18      143     2       61      228     101     40      144     250     11      76      230     157     28      137     238     127     166     114     9       138     23      103     10      84      106     164     21      9       65      146     67      212     186     0       3       154     113     205     56      230     230     156     4       227     155     159     228     135     136     42      10      163     20      37      144     92      3       19      33      137     228     135     146     169     212     32      187     37      83      21      69      226     24      131     216     0       49      4       36      59      8       191     85      132     242     133     220     252     225     49      53      56      224     227     105     8       16      187     46      20      178     81      228     98      102     40      76      144     248     241     134     82      0       25      250     73      232     146     46      194     222     82      150     116     1       18      90      54      130     46      78      93      194     23      149     96      132     21      33      75      2       130     161     6       8       14      105     199     53      46      139     165     167     28      192     28      212     186     2       113     204     201     181     6       93      82      84      58      18      192     9       151     64      56      82      219     33      49      208     89      3       20      60      153     98      144     66      101     193     254     160     196     37      136     6       72      109     73      23      154     30      145     217     38      98      12      73      12      144     241     6       38      166     84      161     77      252     39      39      17      136     219     131     210     67      18      137     216     39      174     76      60      144     113     41      101     194     110     232     83      0       94      98      66      103     137     27      32      188     132     177     84      92      32      178     148     49      5       180     224     0       57      167     28      211     128     9       197     210     193     205     57      136     1       137     156     38      112     0       225     75      2       14      32      188     76      8       56      49      0       228     79      4       107     226     31      169     13      8       56      51      132     192     160     176     24      160     198     98      17      1       14      162     66      242     15      36      197     30      65      192     3       108     50      72      100     134     16      121     34      67      145     47      98      0       49      4       78      57      140     0       192     98      54      112     4       133     228     57      162     24      196     2       12      68      
 === SpecificData =================================

 [Specific eLENS_SPECIFIC_RELATIVEILLUMINANCE3D Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6026
 0x6026 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_WIDE_ACTUAL_F_NUMBER_3D Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6027
 0x6027 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_OPEN_ACTUAL_F_NUMBER_3D Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6028
 0x6028 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_NORMINAL_F_NUMBER_3D Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6029
 0x6029 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_T_NUMBER_3D Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x602a
 0x602a : I don't have info about this code 
 [Specific eLENS_SPECIFIC_COLOR_CONTRIBUTION_3D Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x602b
 0x602b : I don't have info about this code 
 [Specific eLENS_SPECIFIC_ZOOM_SPEED Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x5013
 0x5013 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_FOCUS_RANGE_INFO_DUPL Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x602d
 0x602d : I don't have info about this code 
 [Specific eLENS_SPECIFIC_LENS_SHUTTER_LI_CLOSING_TIME Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x602e
 0x602e : I don't have info about this code 
 [Specific eLENS_SPECIFIC_FOCUS_LIMIT_INFO_NEW Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x602f
 0x602f : I don't have info about this code 
 [Specific eLENS_SPECIFIC_FOCUS_RANGE_ADAPT_INFO Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6030
 0x6030 : I don't have info about this code 
 [Specific eLENS_SPECIFIC_D_VALUE_DUPL Data iRet = 8198, Length = 0]
 === SpecificData =================================
 SpecificCode = 0x6031
[root@drime5 ~]# st cap lens pdget
 0x6031 : I don't have info about this code 
 [Property eLENS_PROPERTY_COMMUNICATION_MODE iRet = 8194] Data = 0x1    
 [Property eLENS_PROPERTY_ELECTRIC_MF_PERMISSION iRet = 8194] Data = 0x1        
 [Property eLENS_PROPERTY_FOCUS_MODE iRet = 8194] Data = 0x0    
 [Property eLENS_PROPERTY_FOCUS_LIMIT iRet = 8199] Data = 0x0   
 [Property eLENS_PROPERTY_TILT_FUNCTION iRet = 8199] Data = 0x0 
 [Property eLENS_PROPERTY_SHIFT_FUNCTION iRet = 8199] Data = 0x0        
 [Property eLENS_PROPERTY_ZOOM_POINT iRet = 8194] Data = 0x1    
 [Property eLENS_PROPERTY_IRIS_POINT iRet = 8194] Data = 0x1    
 [Property eLENS_PROPERTY_OIS_AVAILABILITY iRet = 8194] Data = 0x1      
 [Property eLENS_PROPERTY_TEMPERATURE iRet = 8199] Data = 0x0   0x0     
 [Property eLENS_PROPERTY_FOCUS_POSITION iRet = 8194] Data = 0x32       0x4     
 [Property eLENS_PROPERTY_ZOOM_TRACKING_PERMISSION iRet = 8194] Data = 0x0      
 [Property eLENS_PROPERTY_OPERATION_METHOD_PERMISSION iRet = 8194] Data = 0x10  
 [Property eLENS_PROPERTY_MF_RING_EVENT_PROHIBITION iRet = 8194] Data = 0x0     
 [Property eLENS_PROPERTY_THREE_DIM iRet = 8199] Data = 0x0     
 [Property eLENS_PROPERTY_ELECTRIC_ZOOM_PERMISSION iRet = 8194] Data = 0x0      
 [Property eLENS_PROPERTY_ZOOM_POINT_DT iRet = 8194] Data = 0x0 0x1     
 [Property eLENS_PROPERTY_LENS_SHUTTER_LI_POINT iRet = 8199] Data = 0x0 
 [Property eLENS_PROPERTY_ZOOM_SPEED  iRet = 8194] Data = 0x1   
 [Property eLENS_PROPERTY_MF_SENSITIVITY iRet = 8194] Data = 0x0        
 [Property eLENS_PROPERTY_FOCUS_RANGE_ADAPT_PERMISSION iRet = 8199] Data = 0x0  
 [Property eLENS_PROPERTY_FOCUS_RANGE_ADAPT_SELECT iRet = 8199] Data = 0x0      
[root@drime5 ~]# st cap lens zoom 
CurZoomPoint : 1 CurZoomPointDT : 1, 256
[root@drime5 ~]# st cap lens focus_pos
lFurthestPosition : 971
lNearestPosition  : 1203
lCurrentPosition  : 1074
ActualFNumberForAF  : 59
[root@drime5 ~]# st cap lens spi                          
usage:  st cap lens spi [param] [param]
                * param list *
                [mode] [value]
                        - select mode
                [enable]
                        - spi enable
                [disable]
                        - spi disable
[root@drime5 ~]# st cap lens af   
InfinityPosition : 971
InfPositionTemp  : -3
NearPosition     : 1203
NearTempPosition : 2
[root@drime5 ~]# st cap lens getrange 
Focus Range is Max = 4727, Min = 805 
Iris Range  is Max = 26, Min = 1 
[root@drime5 ~]# st cap lens lensinfo
lensinfo.bLensSpecID                    = 15
lensinfo.blAFAvailable                  = 1
lensinfo.blOISAvaiable                  = 1
lensinfo.blContrastAvailable    = 1
lensinfo.blZoomLens                             = 1
lensinfo.blZoomFunction                 = 1
lensinfo.blMFSwitch                             = 0
lensinfo.blMFRing                               = 0
lensinfo.blOISSwitch                    = 0
lensinfo.blIFunction                    = 1
lensinfo.blFocusLimitSwitch             = 0
lensinfo.blFocusLimitAvailable  = 0
lensinfo.focus_custom_limit_available   = 0
lensinfo.blDistanceBarEnable    = 0
lensinfo.blMFSensSetAvailable   = 1
lensinfo.blFTMFEnable                   = 0
lensinfo.bl3DAvailable                  = 0
lensinfo.wFocusMax                              = 4727
lensinfo.wFocusMin                              = 805
lensinfo.bLDCStatus                             = 1
lensinfo.bLensSegment                   = 5
lensinfo.bISettingInfo                  = 0
lensinfo.bFWversion                             = 01.30_01.50
lensinfo.blDISDisableLens               = 0
lensproperty.mf_operate_mode        =0
lensproperty.af_switch_mode         =4
lensproperty.communication_mode     =7
lensproperty.lens_locked_mode       =10
lensproperty.communication_error    =0
lensproperty.fatal_error            =0
lensproperty.ifunc_control_mode     =0
lensproperty.ois_switch_mode        =15
lensproperty.zoom_point             =1
lensproperty.iris_point             =1
lensproperty.focus_limit_mode       =0
lensproperty.upgrade_process        =0
lensproperty.focus_position         =971
lensproperty.focus_initialized      =1
lensproperty.w3d_switch_mode        =30
lensproperty.wafmax                 =1203
lensproperty.wafmin                 =971
lensproperty.wfocalmax              =50
lensproperty.wfocalmin              =16
lensproperty.wcurfocal              =16
lensproperty.zoom_point_detail      =256
lensproperty.focus_move_direction   =0
lensproperty.zoom_move_direction    =0
lensproperty.wafovermax             =1243
lensproperty.wafovermin             =931

```
