#Working with Exposure Value 

This applies only to exposure value as measured by the camera (red line on -5...0...+5 bar on the bottom) **on locked shots**. This means it is only applicable to valid shots where the camera has either acheived the focus or the focus is set to manual (and camera only measures exposure on half-press).

Current values are available via the command ```st cap lockinfo``` like this
```
[root@drime5 ~]# st cap lockinfo
----------------------------------------------------------
* Av            :37, FnoNum       :22, FnoDen   :10 
* Tv            :117, ShSpdNum     : 1, ShSpdDen :160 
* DeltaEv       :10 
* ExpOutOfRange :1 
* FlashFire     :0 
* HandshakeFlag :0 
* Iso           :200 
* MultiAreaX    :0, nMultiAreaY    :0 
----------------------------------------------------------
* AfResult1     :0x00000010 
* AfResult2     :0x00000000 
----------------------------------------------------------
* Fd            :0 
* caf           :0 
* LargeWin      :1 
* ExtendArea    :0 
* FcousLensInit :1 
----------------------------------------------------------
* SmartScene    :0 
* SubSmartScene :0 
* SmartWarning  :0 
* EvNum         :10 
* EvDen         :10 
* EvDen         :10 
* UnderFlag     :0 
----------------------------------------------------------
* BAGEvNum      :0 
* BAGEvDen      :0 
* Paf           :0 
----------------------------------------------------------
* fd run        :0 
* fd disp stop  :0 
* fd mark       :0 
----------------------------------------------------------
```

There is a wealth of information available, but the most interesting ones to us are:
  - Tv = LOG(Shutter Speed)/LOG(2)*16
  - Shutter Speed = 2^(Tv/16)
  - Av = LOG(A)/LOG(2)*32
  - A  = 2^*(Av/32)
  - FnoNum = A*10
  - FnoDen = Factor (22 -> 2.2)
  - DeltaEV = Over/under-exposure = LOG(E)/LOG(2)*16
  - Iso = ISO
  - ShSpdDen = 1/SS
  - ShSpdNum = 1 
  - BAGEvNum = Exposure Compensation * 10

Difference for one stop
  - Tv, DeltaEv, Av +-16
  - BAGEvNum +- 10

If we want to change the value of some parameter, we can do it via the ```st cap capdtm setvar``` command like this 

```
[root@drime5 ~]# st cap capdtm getvar TV      
Variable Data is 0x00000000_0000007d
[root@drime5 ~]# st cap capdtm setvar TV 100 4
VariableData is set
[root@drime5 ~]# st cap capdtm getvar TV      
Variable Data is 0x00000000_00000064
```

More information on that command [here](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/ST_CAP_CAPDTM.md).
Do note that values wrap around 2^16 (65536) so that the negative values are 65535-VALUE.

Additional information for scene (even not locked, but not EV value) can be obtained by ```st cap iqr``` like this

```
[root@drime5 ~]# st cap iqr
     +-----------------------------------------+-------------------------------+-----------+-----------+
     + IQ Data Repeater Name                   + IQ Data Repeater Value        + Value(Dec)+ Value(Hex)+
     +-----------------------------------------+-------------------------------+-----------+-----------+
[  0]| eIQ_ID_AF_MODE                          | eFOCUS_MODE_SINGLE            |          0| 0x00000000|
[  1]| eIQ_ID_AF_MOVIE_MODE                    | eFOCUS_MOVIE_MODE_CONTINUOUS  |          1| 0x00000001|
[  2]| eIQ_ID_AF_AREA                          | eFOCUS_AREA_SELECTION_AF      |          0| 0x00000000|
[  3]| eIQ_ID_AF_MF_ASSIST_MODE                | eMFASSIST_ENLARGEx5           |          1| 0x00000001|
[  4]| eIQ_ID_AF_ASSIST_LAMP                   | eAF_ASSIST_LAMP_OFF           |          0| 0x00000000|
[  5]| eIQ_ID_AF_LOCK_STATUS                   | eAF_LOCK_STATUS_OFF           |          0| 0x00000000|
[  6]| eIQ_ID_AF_FOCUS_LIMIT_STATUS            | eAF_FOCUS_LISMIT_AUTO_MACRO   |          0| 0x00000000|
[  7]| eIQ_ID_AF_AREA_POSITION_X               |    -                          |        360| 0x00000168|
[  8]| eIQ_ID_AF_AREA_POSITION_Y               |    -                          |        144| 0x00000090|
[  9]| eIQ_ID_AF_AREA_SIZE_WIDTH               |    -                          |         64| 0x00000040|
[ 10]| eIQ_ID_AF_AREA_SIZE_HEIGHT              |    -                          |         64| 0x00000040|
[ 11]| eIQ_ID_AF_AREA_SML_SIZE_WIDTH           |    -                          |         36| 0x00000024|
[ 12]| eIQ_ID_AF_AREA_SML_SIZE_HEIGHT          |    -                          |         43| 0x0000002B|
[ 13]| eIQ_ID_AF_AREA_LAR_SIZE_WIDTH           |    -                          |         64| 0x00000040|
[ 14]| eIQ_ID_AF_AREA_LAR_SIZE_HEIGHT          |    -                          |         64| 0x00000040|
[ 15]| eIQ_ID_AF_IMAGE_SIZE_WIDTH              |    -                          |        720| 0x000002D0|
[ 16]| eIQ_ID_AF_IMAGE_SIZE_HEIGHT             |    -                          |        480| 0x000001E0|
[ 17]| eIQ_ID_AF_FOCUS_AID_PEAK                |    -                          |          0| 0x00000000|
[ 18]| eIQ_ID_AF_FOCUS_AID_A                   |    -                          |          0| 0x00000000|
[ 19]| eIQ_ID_AF_FOCUS_AID_C                   |    -                          |          0| 0x00000000|
[ 20]| eIQ_ID_AF_RESULT1                       |    -                          |          1| 0x00000001|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[ 21]| eIQ_ID_AF_RESULT2                       |    -                          | 1073741824| 0x40000000|
[ 22]| eIQ_ID_AF_RESULT_MAIN_AREA              |    -                          |          0| 0x00000000|
[ 23]| eIQ_ID_AF_RESULT_START_H                |    -                          |        360| 0x00000168|
[ 24]| eIQ_ID_AF_RESULT_START_V                |    -                          |        144| 0x00000090|
[ 25]| eIQ_ID_AF_READOUT_HOFFSET               |    -                          |         32| 0x00000020|
[ 26]| eIQ_ID_AF_READOUT_VOFFSET               |    -                          |         20| 0x00000014|
[ 27]| eIQ_ID_AF_READOUT_WIDTH                 |    -                          |       2160| 0x00000870|
[ 28]| eIQ_ID_AF_READOUT_HEIGHT                |    -                          |       1444| 0x000005A4|
[ 29]| eIQ_ID_AF_TOUCH_AF                      |    -                          |          0| 0x00000000|
[ 30]| eIQ_ID_AF_MANUAL_MULTI_AF               | AUTO                          |          0| 0x00000000|
[ 31]| eIQ_ID_AF_S2_PUSHED                     |    -                          |          0| 0x00000000|
[ 32]| eIQ_ID_AF_MOVIE_SPEED                   | eAF_MOVIE_SPEED_FAST          |          0| 0x00000000|
[ 33]| eIQ_ID_AF_MOVIE_SENSITIVITY             | eAF_MOVIE_SENSITIVITY_LEV3    |          2| 0x00000002|
[ 34]| eIQ_ID_AF_MULTIAREA                     | eFOCUS_MULTIFULL_AREA         |          0| 0x00000000|
[ 35]| eIQ_ID_AF_ZONEAREA                      | eFOCUS_ZONE7X5_AREA           |          0| 0x00000000|
[ 36]| eIQ_ID_METERING_MODE                    | eMETERING_MULTI               |          0| 0x00000000|
[ 37]| eIQ_ID_MOVIE_AE                         | eMOVIE_AE_M                   |          3| 0x00000003|
[ 38]| eIQ_ID_EV_STEP                          | eEV_STEP_ONEHALF              |          0| 0x00000000|
[ 39]| eIQ_ID_FLASH_MODE                       | eSTROBO_OFF                   |          0| 0x00000000|
[ 40]| eIQ_ID_FLASH_WIRELESS_SYNC              | eSTROBO_WIRELESS_SYNC_OFF     |          0| 0x00000000|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[ 41]| eIQ_ID_FLASH_WIRELESS_MODE_MASTER       | eSTROBO_WIRELESS_SYNC_OFF     |          0| 0x00000000|
[ 42]| eIQ_ID_FLASH_WIRELESS_MODE_GROUPA       | eSTROBO_WIRELESS_SYNC_OFF     |          0| 0x00000000|
[ 43]| eIQ_ID_FLASH_WIRELESS_MODE_GROUPB       | eSTROBO_WIRELESS_SYNC_OFF     |          0| 0x00000000|
[ 44]| eIQ_ID_FLASH_WIRELESS_MODE_GROUPC       | eSTROBO_WIRELESS_SYNC_OFF     |          0| 0x00000000|
[ 45]| eIQ_ID_FLASH_WIRELESS_EV_MASTER         |    -                          |          0| 0x00000000|
[ 46]| eIQ_ID_FLASH_WIRELESS_EV_GROUPA         |    -                          |          0| 0x00000000|
[ 47]| eIQ_ID_FLASH_WIRELESS_EV_GROUPB         |    -                          |          0| 0x00000000|
[ 48]| eIQ_ID_FLASH_WIRELESS_EV_GROUPC         |    -                          |          0| 0x00000000|
[ 49]| eIQ_ID_FLASH_WIRELESS_MS_MASTER         |    -                          |          0| 0x00000000|
[ 50]| eIQ_ID_FLASH_WIRELESS_MS_GROUPA         |    -                          |          0| 0x00000000|
[ 51]| eIQ_ID_FLASH_WIRELESS_MS_GROUPB         |    -                          |          0| 0x00000000|
[ 52]| eIQ_ID_FLASH_WIRELESS_MS_GROUPC         |    -                          |          0| 0x00000000|
[ 53]| eIQ_ID_FRAME_RATE                       |    -                          |          5| 0x00000005|
[ 54]| eIQ_ID_AEB_STEP                         | eAEB_STEP_EVC_3               |          1| 0x00000001|
[ 55]| eIQ_ID_AEB_ORDER                        | eAEB_ORDER_P_Z_M              |          1| 0x00000001|
[ 56]| eIQ_ID_SELECT_AREA_AE                   | eSELECT_AREA_AE_ON            |          1| 0x00000001|
[ 57]| eIQ_ID_EVC                              |    -                          |         10| 0x0000000A|
[ 58]| eIQ_ID_FLASH_EV_EV                      |    -                          |         10| 0x0000000A|
[ 59]| eIQ_ID_FLASH_EV_DEN                     |    -                          |          0| 0x00000000|
[ 60]| eIQ_ID_BRACKET_NUMBER                   |    -                          |         -1| 0xFFFFFFFF|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[ 61]| eIQ_ID_CONT_SHOOTING_NUMBER             |    -                          |          0| 0x00000000|
[ 62]| eIQ_ID_ISO_SETTING                      |    -                          |        200| 0x000000C8|
[ 63]| eIQ_ID_ISO_MAX_SETTING                  |    -                          |       6400| 0x00001900|
[ 64]| eIQ_ID_TV_SETTING                       |    -                          |         91| 0x0000005B|
[ 65]| eIQ_ID_AV_SETTING                       |    -                          |         48| 0x00000030|
[ 66]| eIQ_ID_SHUTTER_SPEED_NUM                |    -                          |          0| 0x00000000|
[ 67]| eIQ_ID_SHUTTER_SPEED_DEN                |    -                          |          0| 0x00000000|
[ 68]| eIQ_ID_IDEPTH                           |    -                          |          0| 0x00000000|
[ 69]| eIQ_ID_DEPTH_BRACKET                    | eDEPTH_BRACKET_STEP_EVC_10    |          3| 0x00000003|
[ 70]| eIQ_ID_AE_AREA_POSITION_X               |    -                          |        360| 0x00000168|
[ 71]| eIQ_ID_AE_AREA_POSITION_Y               |    -                          |        144| 0x00000090|
[ 72]| eIQ_ID_AE_AREA_SIZE_WIDTH               |    -                          |         64| 0x00000040|
[ 73]| eIQ_ID_AE_AREA_SIZE_HEIGHT              |    -                          |         64| 0x00000040|
[ 74]| eIQ_ID_AE_IMAGE_SIZE_WIDTH              |    -                          |        720| 0x000002D0|
[ 75]| eIQ_ID_AE_IMAGE_SIZE_HEIGHT             |    -                          |        480| 0x000001E0|
[ 76]| eIQ_ID_AE_MOVIE_DIS                     | eMOVIE_DIS_OFF                |          0| 0x00000000|
[ 77]| eIQ_ID_SMARTRANGE_CONFIG                | eSMARTRANGE_HDR_MIDDLE        |          3| 0x00000003|
[ 78]| eIQ_ID_SMARTRANGE_MOVIE                 | eSMARTRANGE_OFF               |          0| 0x00000000|
[ 79]| eIQ_ID_EFFECT_MODE                      | eEFFECT_NORMAL                |          0| 0x00000000|
[ 80]| eIQ_ID_PW_COLOR                         |    -                          |         -1| 0xFFFFFFFF|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[ 81]| eIQ_ID_PW_COLOR_R                       |    -                          |  134217983| 0x080000FF|
[ 82]| eIQ_ID_PW_COLOR_G                       |    -                          |  134217983| 0x080000FF|
[ 83]| eIQ_ID_PW_COLOR_B                       |    -                          |  134217983| 0x080000FF|
[ 84]| eIQ_ID_PW_HUE                           |    -                          |    1038346| 0x000FD80A|
[ 85]| eIQ_ID_PW_SATURATION                    |    -                          |    1038346| 0x000FD80A|
[ 86]| eIQ_ID_PW_SHARPNESS                     |    -                          |    1038346| 0x000FD80A|
[ 87]| eIQ_ID_PW_CONTRAST                      |    -                          |    1038346| 0x000FD80A|
[ 88]| eIQ_ID_COLOR_SPACE                      | eCOLOR_SPACE_SRGB             |          0| 0x00000000|
[ 89]| eIQ_ID_HIGH_ISO_NR                      | eHIGH_ISO_NR_MID              |          2| 0x00000002|
[ 90]| eIQ_ID_LONG_TIME_NR                     | eIQ_LONG_TIME_NR_ON           |          1| 0x00000001|
[ 91]| eIQ_ID_MF_MAGNIFY_OFFSET_X              |    -                          |       2340| 0x00000924|
[ 92]| eIQ_ID_MF_MAGNIFY_OFFSET_Y              |    -                          |       1528| 0x000005F8|
[ 93]| eIQ_ID_MAX_G                            |    -                          |          0| 0x00000000|
[ 94]| eIQ_ID_DIFF_G                           |    -                          |          0| 0x00000000|
[ 95]| eIQ_ID_BULB_TIME                        |    -                          |          0| 0x00000000|
[ 96]| eIQ_ID_HDR_TYPE                         | eIQ_HDR_TYPE_NONE             |          0| 0x00000000|
[ 97]| eIQ_ID_WB_MODE                          | eWB_MODE_AUTO                 |          0| 0x00000000|
[ 98]| eIQ_ID_WB_TYPE                          | eWB_TYPE_LIVEVIEW             |          0| 0x00000000|
[ 99]| eIQ_ID_WB_COLORTEMP                     |    -                          |          0| 0x00000000|
[100]| eIQ_ID_WB_ADJUST_AB                     |    -                          |          7| 0x00000007|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[101]| eIQ_ID_WB_ADJUST_MG                     |    -                          |          7| 0x00000007|
[102]| eIQ_ID_WB_BRACKET_AB                    |    -                          |          3| 0x00000003|
[103]| eIQ_ID_WB_BRACKET_MG                    |    -                          |          0| 0x00000000|
[104]| eIQ_ID_WB_BA_X                          |    -                          |          0| 0x00000000|
[105]| eIQ_ID_WB_GM_Y                          |    -                          |          0| 0x00000000|
[106]| eIQ_ID_WB_KELVIN                        |    -                          |       5500| 0x0000157C|
[107]| eIQ_ID_CWB_R_GAIN                       |    -                          |     179200| 0x0002BC00|
[108]| eIQ_ID_CWB_B_GAIN                       |    -                          |     115200| 0x0001C200|
[109]| eIQ_ID_CWB_G_GAIN                       |    -                          |      65536| 0x00010000|
[110]| eIQ_ID_OLED_COLOR                       | eOLED_COLOR_OFF               |          0| 0x00000000|
[111]| eIQ_ID_APP_MODE                         | eAPPMODE_MANUAL               |          5| 0x00000005|
[112]| eIQ_ID_FRAMING_MODE                     | eFRAMING_MODE_OFF             |          0| 0x00000000|
[113]| eIQ_ID_ROTATION_POSITION                | eROTATE_POSITION_0            |          0| 0x00000000|
[114]| eIQ_ID_BRACKET_TYPE                     | eBRACKET_TYPE_EXPOSURE        |          0| 0x00000000|
[115]| eIQ_ID_SHOOTING_MODE                    | eSHOOTING_SINGLE              |          0| 0x00000000|
[116]| eIQ_ID_EFS_MODE                         | eEFS_NORMAL                   |          1| 0x00000001|
[117]| eIQ_ID_LDC_STATUS                       | eLDC_ON                       |          1| 0x00000001|
[118]| eIQ_ID_IS_MOVIE_RECORDING               | eIS_MOVIE_RECORDING_FALSE     |          0| 0x00000000|
[119]| eIQ_ID_CAPTURE_MODE                     | eCAPTURE_MODE_M               |          4| 0x00000004|
[120]| eIQ_ID_MOVIESIZE                        | eMOVIESIZE_FHD                |          0| 0x00000000|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[121]| eIQ_ID_MOVIE_FRAME_RATE                 |    -                          |          0| 0x00000000|
[122]| eIQ_ID_3D_MODE                          | e3D_MODE_SWITCH_OFF           |          0| 0x00000000|
[123]| eIQ_ID_3D_AUTO_MODE                     | e3D_AUTO_MODE_ON              |          1| 0x00000001|
[124]| eIQ_ID_3D_BUTTERFLY                     | e3D_MODE_SWITCH_OFF           |          0| 0x00000000|
[125]| eIQ_ID_3D_FRAMERATE                     |    -                          |          0| 0x00000000|
[126]| eIQ_ID_WIFI_MODE                        | eWIFI_MODE_OFF                |          0| 0x00000000|
[127]| eIQ_ID_DIGITAL_ZOOM_RATIO               |    -                          |          0| 0x00000000|
[128]| eIQ_ID_SMARTART_MODE                    | eSMARTART_MODE_OFF            |          0| 0x00000000|
[129]| eIQ_ID_SMARTART_CATEGORY                | eSMARTART_CTG_BEAUTY_PORTRAIT |          0| 0x00000000|
[130]| eIQ_ID_SMARTART_BEAUTYSHOT_STATE        |    -                          |          0| 0x00000000|
[131]| eIQ_ID_SMARTART_LENSEFFECT_STATE        |    -                          |          0| 0x00000000|
[132]| eIQ_ID_SMARTART_CONTSHOT_STATE          |    -                          |          0| 0x00000000|
[133]| eIQ_ID_SMARTART_HDR_STATE               |    -                          |          0| 0x00000000|
[134]| eIQ_ID_SMARTART_HDRART_STATE            |    -                          |          0| 0x00000000|
[135]| eIQ_ID_SMARTART_LLS_STATE               |    -                          |          0| 0x00000000|
[136]| eIQ_ID_SMARTART_SHUTTER_STATE           |    -                          |          0| 0x00000000|
[137]| eIQ_ID_SMARTART_APERTURE_STATE          |    -                          |          0| 0x00000000|
[138]| eIQ_ID_SMARTART_CONTRAST_STATE          |    -                          |          0| 0x00000000|
[139]| eIQ_ID_SMARTART_SHARPNESS_STATE         |    -                          |          0| 0x00000000|
[140]| eIQ_ID_SMARTART_SATURATION_STATE        |    -                          |          0| 0x00000000|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[141]| eIQ_ID_SMARTART_CCM_STATE               |    -                          |          0| 0x00000000|
[142]| eIQ_ID_SMARTART_EXPOSURE_STATE          |    -                          |          0| 0x00000000|
[143]| eIQ_ID_SMARTART_COLORTEMP_STATE         |    -                          |          0| 0x00000000|
[144]| eIQ_ID_SMARTART_BEAUTYTONE_LEVEL        |    -                          |          0| 0x00000000|
[145]| eIQ_ID_SMARTART_BEAUTYRETOUCH_LEVEL     |    -                          |          0| 0x00000000|
[146]| eIQ_ID_SMARTART_LENSEFFECT_LEVEL        |    -                          |          0| 0x00000000|
[147]| eIQ_ID_SMARTART_CONTSHOT_LEVEL          |    -                          |          0| 0x00000000|
[148]| eIQ_ID_SMARTART_SHUTTER_LEVEL           |    -                          |          0| 0x00000000|
[149]| eIQ_ID_SMARTART_APERTURE_LEVEL          |    -                          |          0| 0x00000000|
[150]| eIQ_ID_SMARTART_CONTRAST_LEVEL          |    -                          |          0| 0x00000000|
[151]| eIQ_ID_SMARTART_SATURATION_LEVEL        |    -                          |          0| 0x00000000|
[152]| eIQ_ID_SMARTART_SHARPNESS_LEVEL         |    -                          |          0| 0x00000000|
[153]| eIQ_ID_SMARTART_CCM_LEVEL               |    -                          |          0| 0x00000000|
[154]| eIQ_ID_SMARTART_EXPOSURE_LEVEL          |    -                          |          0| 0x00000000|
[155]| eIQ_ID_SMARTART_COLORTEMP_LEVEL         |    -                          |          0| 0x00000000|
[156]| eIQ_ID_SMART_PRO_MODE                   | eSMARTPRO_MODE_BEAUTY_FACE    |          0| 0x00000000|
[157]| eIQ_ID_SMART_PRO_LEVEL                  |    -                          |          0| 0x00000000|
[158]| eIQ_ID_SMARTAUTO_ADSCENE_RESULT         |    -                          |          0| 0x00000000|
[159]| eIQ_ID_LLS_MARK                         |    -                          |          0| 0x00000000|
[160]| eIQ_ID_IMG_ASPECT_RATIO                 | eIQ_IMG_ASPECT_RATIO_3_2      |          2| 0x00000002|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[161]| eIQ_ID_SHUTTER_MIN                      | eSHUTTER_MIN_OFF              |          0| 0x00000000|
[162]| eIQ_ID_TV_SETTING_LIMIT                 |    -                          |          0| 0x00000000|
[163]| eIQ_ID_SMART_PRO_WARNINGMSG             |    -                          |          0| 0x00000000|
[164]| eIQ_ID_TEMPERATURE                      |    -                          |          0| 0x00000000|
[165]| eIQ_ID_SMARTFILTER                      | eIQ_SMARTFILTER_OFF           |          0| 0x00000000|
[166]| eIQ_ID_BABYMONITOR                      | eBABY_MONITOR_MODE_OFF        |          0| 0x00000000|
[167]| eIQ_ID_DMAOverRun_STATUS                |    -                          |          0| 0x00000000|
[168]| eIQ_ID_D4CWRITE_RUN_STATUS              |    -                          |          0| 0x00000000|
[169]| eIQ_ID_CONTI_CAPTURING                  |    -                          |          0| 0x00000000|
[170]| eIQ_ID_HIGHCONTI_FPS                    |    -                          |          0| 0x00000000|
[171]| eIQ_ID_BRIGHT_ADJUST_GUIDE              | eIQ_BRIGHTADJUSTGUIDE_OFF     |          0| 0x00000000|
[172]| eIQ_ID_AUTOSHUTTER_SUBMODE              | eAUTOSHUTTER_SUBMODE_BASEBALL |          0| 0x00000000|
[173]| eIQ_ID_POWEROFF_STATUS                  |    -                          |          0| 0x00000000|
[174]| eIQ_ID_3D_MODE_CAPTURING                |    -                          |          0| 0x00000000|
[175]| eIQ_ID_HDMI_CONNECT                     |    -                          |          0| 0x00000000|
[176]| eIQ_ID_HDMI_SIZE                        |    -                          |          0| 0x00000000|
[177]| eIQ_ID_VIDEO_OUT                        | eIQ_VIDEOOUT_NTSC             |          0| 0x00000000|
[178]| eIQ_ID_AFPRIORITYRLS                    | eIQ_AFPRIORITYRLS_OFF_BALANCE |          1| 0x00000001|
[179]| eIQ_ID_SRA_WB_UPDATE                    |    -                          |          0| 0x00000000|
[180]| eIQ_ID_MOVIE_GAMMA_MODE                 | eIQIF_MOVIE_GAMMA_NORMAL      |          0| 0x00000000|
     +-----------------------------------------+-------------------------------+-----------+-----------+
[181]| eIQ_ID_MOVIE_MASTER_BLACK_LEVEL         |    -                          |          0| 0x00000000|
[182]| eIQ_ID_MOVIE_LUMINANCE_LEVEL            | eIQIF_MOVIE_LUMINANCE_0_255   |          0| 0x00000000|
[183]| eIQ_ID_SHUTTER_KEY_STATE                | eIQ_SHUTTER_KEY_STATE_S0      |          0| 0x00000000|
     +-----------------------------------------+-------------------------------+-----------+-----------+

[root@drime5 ~]# st cap iqr 64     
     +-----------------------------------------+-------------------------------+-----------+-----------+
     + IQ Data Repeater Name                   + IQ Data Repeater Value        + Value(Dec)+ Value(Hex)+
     +-----------------------------------------+-------------------------------+-----------+-----------+
[ 64]| eIQ_ID_TV_SETTING                       |    -                          |        133| 0x00000085|
     +-----------------------------------------+-------------------------------+-----------+-----------+
```

This is an example output for NX500.

##Smoothing EV Change During Time-Lapse

We can combine previous data to smooth changes in EV during timelapses (day-to-night and similar) by controlling the shutter speed (Note: if using full electronic shutter on NX500 you cannot go slower that ~1/30s).

In order to avoid flickering (which we get if we leave the camera in P, A or S modes) we need to put camera to M and "smooth" the changes by, for example, using rolling average of EV value over the past 5 frames and also comparing if we have sudden spikes in exposure (so we ignore spikes of 1 or 2 measurements).

For example, here is a functional C program that will **very slowly** adjust the exposure 
(you can play around with ```rolling=0, threshold=3, steps=5```):

```
#include <stdio.h>
#include <strings.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>
#include <math.h>

static int ev_values[255], ev_step=0, debug=0, Tv=0, delay=1, rolling=0, threshold=3, steps=5;
static char stringline[255];

static void run_command(char *command)
{
	if (debug) printf("CMD: %s\n", command);
	char *cmd;
	asprintf(&cmd, "%s", command);
	system(cmd);
	free(cmd);
	if (debug) printf(" done.\n");
}


void ev_smooth_clean(int steps, int value) {
	int i;
	if (value==0) {
		for(i=0;i<steps;i++) ev_values[i]=value;
	} else {
		for(i=0;i<steps;i++) ev_values[i]+=value;
	}
}

void ev_smooth(int steps) {
	int ev_get() {
		FILE *fp;
		char *spl = "";
		int Ev=0;
		
		fp = popen("/bin/bash -c \"/usr/bin/st key push s1; /usr/bin/st key release s1; /usr/bin/st cap lockinfo\"", "r");
		
		if (fp == NULL) {
			if (debug) printf("Failed to get current EV data\n");
			return 0;
		} else {
			if ((fgets(stringline, sizeof(stringline) - 1, fp) != NULL) && (fgets(stringline, sizeof(stringline) - 1, fp) != NULL) &&(fgets(stringline, sizeof(stringline) - 1, fp) != NULL)) {
				stringline[0] = '_';	// fix st output
				spl = strtok(stringline, ":");
				spl = strtok(NULL, ",");
				Tv=atoi(spl);
				if (fgets(stringline, sizeof(stringline) - 1, fp) != NULL) {
					stringline[0] = '_';	// fix st output
					spl = strtok(stringline, ":");
					spl = strtok(NULL, " ");
					Ev=atoi(spl);
					if (debug) printf("Tv: %d\tEv: %d\n",Tv,Ev);
				}
			} else {
				printf("Error reding from file. Stringline: %s\n",stringline);
			}
			pclose(fp);
			if (debug==2) {
				return 16-rand()%20;
			}
			return Ev;
		}
	}

	int i, sum=0, deltaEv=0, newTv=0;
	float avg=0.0;
	char *cmd;
	ev_values[ev_step]=ev_get();
	for(i=0;i<steps;i++) {
		sum+=ev_values[i];
		printf("%d\t",ev_values[i]);
	}
	printf("\n");
	avg=(float)sum/steps;
	printf("AVG: %f\n",avg);
	if ((abs(avg)+0.05)>threshold) {
		sum=0;
		for(i=0;i<steps;i++) {
			if ((avg>0 && ev_values[i]>=threshold) || (avg<0 && ev_values[i]<=threshold)) sum++;
		}
		if (sum>(steps/2)) {
			deltaEv = (int)round(avg/abs(avg))*threshold;
			newTv = Tv + deltaEv;
			printf("Adjusting shutter by %d to %d (%d points above %d)\n",deltaEv, newTv, sum, steps/2);
			if (debug<2) {
				asprintf(&cmd,"st cap capdtm setvar TV %d 4",newTv);
				sleep(1);
				run_command(cmd);
			}
			if (rolling==1) ev_smooth_clean(steps, -deltaEv);
			else ev_smooth_clean(steps, 0);
		} 
	}
	ev_step++;
	if (ev_step>=steps) {
		ev_step=0;
	}
}

int main(int argc, char **argv)
{
	int i;
	if (argc>1) debug=atoi(argv[1]);
	if (argc>2) delay=atoi(argv[2]);
	if (argc>3) steps=atoi(argv[3]);
	if (argc>4) rolling=atoi(argv[4]);
	ev_smooth_clean(steps,0);
	for(i=0;i<1000;i++) {
		printf("STEP: %d\n",i);
		ev_smooth(steps);
		sleep(delay);
	}
}
```

This is all implemented in [mod_lapse](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/mod_lapse?raw=true) tool, with sources [here](https://github.com/ottokiksmaler/nx500_nx1_modding/blob/master/mod_lapse.c)
