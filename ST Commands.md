#ST Commands

Misc usage instructions included in various placen in firmware

```
st app nx menu test-mode: set the test mode configuration
st app nx menu format: format the card
st app nx menu flash [mode]: adjust flash options
        off,auto,fill-in,fill-in-red,curtain-1,curtain-2,smart
st app nx menu powersave [on,off]: enable/disable power save operation
st app nx menu afmode [single,caf,auto,manual]: set AF mode
st app nx menu s2-trace [on,off]: enable/diable S1/S2 monitoring log
st app nx menu capture-end-trace [on,off]: enable/diable capture end operation monitoring log
st app nx menu full-af-box [on,off]: enable/diable show all AF boxes or specified ones
st app nx menu af-box-cluster [on,off]: enable/diable smooth AF box display
st app nx menu af-box set w h: set the af box display area as wxh size
st app nx menu af-box: show the current af box configuration

st app nx mode [show,name]: show the mode list or change to specified mode
st app nx run stop: stop currently running test scenario
st app nx run rand-move: runs random key input test
st app nx run rand-move: runs menu/smart panel/playback mode random move test

Usage: st app nx capture [cmd1,...]
  single: do single capture (send S1/S2 key event)
  resolution [show,name]: set photo resolution
  run stop       stop test running
  run count [n]  set the max test count as given value (0: infinite)
  run unit       do single capture unit test
  run single     do single capture while changing photo resolution
  run drive-unit do capture while changing drive mode
  run drive      do capture while changing drive and photo resolution
  run basic      do capture test while changing mode and photo resolution
  run full       do full integration capture test
  run cap-ready  do liveview check after S2 completed
  af-mode [single,caf,auto,manual]: set the af mode
  quality [option]: set the photo quality
     sfine,fine,norm,raw,raw+sfine,raw+fine,raw+norm
  wb [option]: set the white balance options.
     auto,auto-tungsten,tungsten,day,cloud,fluoresent-w,fluoresent-n,fluorescent-d,flash,custom

Timing mark commands:
Usage: st app nx timing [cmd1,...]
  start mask entries [0,1]: start timing loging
  stop: stop the last timing logging
  show: show the timing log to the console
  save filename: save the timing log to given file
  free: free the allocated timing logs
  mask: show the supported timing masks
  print [on,off]: enable or disable direct printf() use for timing mark

Usage: st app nx record [cmd,...]
  start: do record start
  stop: stop video record
  pause: pause current video recording.
  resume: resume current video recording.
  resolution [show,name]: set video record resolution
  run stop       stop current running test
  run count [n]  set the max test count as given value (0: infinite)
  run unit       do video record unit test
  run single     do video recording while changing resolution
  run basic      do record test while changing mode and video resolution
  run full       do full integration video record test

KEY commands:
 st app nx key show: show the list of key names
               push [name]: set the given named key as pressed
               released [name]: set the given named key as released
               single [name]: act as the given named key press and released

usage: st app [command]
           st app help
                          - display help.
           st app info
                          - display evas object informations
           st app foramt
                          - format sd card
           st app usb [mass | ptp | on | off]
                          - setting usb function
                          - mass : set usb type as mass storage
                          - ptp  : set usb type as PTP
                          - on   : connect usb
                          - off  : disconnect usb
           st app rtc [set | get]
                          - set/get rtc value
           st app led [blink| off] [duraion]
                          - handle back led
           st app test [a|b|finit|flash|tt|ps|oor|vconf|f|bodyfw|nolens|affail|logo|spanel]
                          - doing simple action
           st app show [liveview|lock3a|pro_shift]
                          - display some informations
           st app volum [off|low|mid|high]
                          - control volum
           st app bb [lcd|evf|tv][on|off|osd|video]
                          - control black screen
           st app video [lcd|evf|tv][on|off][0|1]
                          - control video black screen
           st app drive [single|conti_n|conti_h|timer|bracket]
                          - control drive
           st app mode [smart-pro|auto|p|a|s|m|custom2|custom1]
                          - control mode 
           st app lens [info|pzoom][tele|wide|stop]
                          - control lens 
           st app set [izoom][1.0|1.2|1.4|1.7|2.0]
           st app set [efs][on|off]
           st app set [sf][off/vig/min/war/neg/red/gr/bl/yel]
           st app set [disp_timer][off/0.5/1/3/5/10]
           st app set [power_timer][off/0.5/1/3/5/10/30]
                          - set menu 
           st app disp [lcd|evf|auto]
                          - control display select      
           st app data [save]
                          - menu setting value control  
           st app isfull
                          - check storage full
           st app wifidirect start/stop
                          - wifidirect autonomous go start, disconnect
           st app power [on]

usage: st writel <address> <value>
usage: st readl <address>

usage: st dump <physical address> <len>
       dump out memory

usage: st log [command]
       st log help
               display help.
       st log enable [all / module name]
               set print level VERBOSE(6) to logutil
       st log disable [all / module name]
               set print level NONE(0) to logutil
       st log setlevel [all / module name] [Level(0-6)]
               set print level for user select 
               - 0: LOGUTIL_TYPE_NONE 
               - 1: LOGUTIL_TYPE_ERROR 
               - 2: LOGUTIL_TYPE_WARNING 
               - 3: LOGUTIL_TYPE_HIGH_LEVEL 
               - 4: LOGUTIL_TYPE_MIDDLE_LEVEL 
               - 5: LOGUTIL_TYPE_LOW_LEVEL 
               - 6: LOGUTIL_TYPE_VERBOSE 
       st log status
               display module debug level status(level is 0-6).
       st log show
       st log reset

usage: st LCD [command]
       st LCD help
       st LCD set [n]
                0 : lcd power on
                1 : lcd power off
                2 : lcd reset
                3 : lcd light on
                4 : lcd light off
                5 : lcd init
                6 : Han Q init

st key getmode  
st key getdrive  

usage: st str [command]
        not enough argument
usage: st cap [command]
usage: st dp [cmd] [arg1] [arg2] ...
       st dp flip grp 0  : None flip.
                  grp 1  : Horizontal flip
                  grp 2  : Vertical flip
                  grp 3  : Both directional flip
       st dp flip vid 0  : None-fliiped.
                  vid 1  : Horizontal flip
                  vid 2  : Vertical flip
                  vid 3  : Both directional flip
usage: st cap [command] [param]

usage: st cap capt [command] [param]
        loglevel
        report
        liveview
        movie
        single start
        conti
        burst
        aeb
        wbb
        pwb
        panorama
        3dshot
        bulb
        cwb
        stop
        trace
        counterlog
        timer
        callback
        mf on / off
        lens init
        iris [open / preview / drive Fnumber]
        ois [, mode]
        quality [sfine / fine / normal / raw / rawsfine / rawfine / rawnormal / sraw]
        size [full / n1 / n2 / n3 / n4 / w1 / w2 / w3 / w4 / s1 / s2 / s3 / s4]
        hdr [off / on / art]
        nr [off / ltnr / adnr]
        init
        strobe [init / charge / on / off / pre]
        still3d
        caf [start / stop]
        ael [on / off]
        afl [on / off]
        smart
        capprint [on / off]
        bestface
        shlag
        3dfps
        event [save / print / test]
        multiexp [, max (count), on/off]
        motionshot [, max (count), on/off]
        light [on / off] [body / strobe]
        conticonti
        portrait
        hdrart
        motionphoto
        lls
        movieaf [start / stop]
        movietouchaf [start / stop]
        focusaid [start / stop]
        dpreview [start / stop]
        pgshift [up / down / reset / countreset]
        fdrun [start / stop]
        objecttrk [start / stop]
        setois [active / idle]
        beauty
        mfenlarge [permit / prohibit / toggle]
        moviefade
        remotevf [start / stop]
        changemode
        iqstub [ae / af / awb / iqif / all] [on / off]
        mcb [category id] [setting id] [length] [data]
        logtest
        sas [trigger]

usage: st cap log [command]
       st cap log help 
               display this information
       st cap log
               dump out capture log.
       st cap log off
               turn off a7 console
       st cap log clear
               clear capture log.

usage: st cap path [command]
       st cap path dump
              dump all registers
       st cap path dump ep
              dump EP registers
       st cap path info
              display all information
       st cap path info ep
              display EP information

usage:  st cap back [command] [param]...
 [command list] 
    uniteset : unit test cmd
    matr : material test command

usage:  st cap back param [param1] [param2]...
 [run/stop Command] 
    st cap back param [run/stop] [still/live/all]
 [clean Command] 
    st cap back param clean [still/live/all]
 [show Command] 
    st cap back param show [still/live/all] [ipc/ldc/rsz/all]
 [cnt Command] 
    st cap back param cnt [display count]
 [status Command] 
    st cap back param status

usage: st cap face [command] [param1] {param2}

usage:    st cap fenx [command] [param]
          * command list *
          [lv]
                  - liveview.
          [still]
                  - still.
          [mv]
                  - movie.
          [gpio]
          [enable 
          [disable
          [setdir in or out
          [setlevel in or out
          [getlevel
                  - check TP1 with GPIO Driver on FrontEnd.
usage:    st cap fenx lv [param]
          * param list *
          [otf]
                  - normal liveview otf.
          [mem]
                  - liveview memory out.
          [120]
                  - normal liveview otf 120fps.
          [stop]
                  - stop.
usage:    st cap fenx still [param]
          [single]
                  - normal single capture.
          [post]
                  - normal single capture post.
          [smat]
                  - normal single capture with Material.
          [postm]
                  - normal single capture post with Material.
          [lrc]
                  - normal signle capture with LRC compress.
          [postlrc]
                  - normal signle capture post with LRC compress.
usage:    st cap fenx mv [param]
          [30]
          [60]
          [capt30]
          [capt60]
          [ud]

Sequencer Debug Command Help :
usage: st cap seq [cmd]
        order [OrderID] [Param (for DebugID)]
        demand [OrderID] [CapNo]
        log
        loglevel [level]
        logid [logID]
        orderid [OrderType(0:Still,1:LView)]
        status
        list [CookNo] [CookNum]
        check [OrderID] [RecipeID(OrderID == 0 Only)]
        wbtest
        dump [on/off] [dump positions...]

usage: st cap live [command] [param1] {param2}
        start
        startPP
        startFisheye
        stopFisheye
        startSSS
        stopSSS
        iZoom n
        rvf
        lock
        unlock
        fade
        adjust
        change
        update
        mfzoom     0 - 1 (0:off/1:on)
        afmode     0 - 2 (0:enable/1:disable/2:fastAF)
        freeze
        release
        loglevel   0 - 9(0:Nothing-9:Always)
        setpath    0 - 2(0:OTF/1:IPCout/2:RawOut/3:Ldc Out/4:120FPS OTF/5:120FPS IPC out
                6:120FPS Raw Out/7:120FPS Ldc Out/8:panorama/9:MFZoom)
        sd      streammode       0 - 14 
                outputdisplay      0 - 6  
                mfzoomenable       0 - 1 (0:off/1:on)
                focuspeakenable    0 - 1 (0:off/1:on)
                sensorframerate    12,15,20,24,25,30,40,50,60,100,120,240
                outputframerate    12,15,20,24,25,30,40,50,60,100,120,240
                adjustmfzoomrate   0 - 4 (OFF,x3,x5,x8,x1)
                pafmode            0 - 1 (0:off/1:on)
                dataframerate      12,15,20,24,25,30,40,50,60,100,120,240
                smartfiltermode    0 - 16 (15:SmartFilerOFF)
                smartautoenable    0 - 1 (0:off/1:on)
                fdenable           0 - 1 (0:off/1:on)
                ldcenable          0 - 1 (0:off/1:on)
                mfassist           0 - 2 (x3,x5,x8)
                zoommagnification  0 - 4 (x1,x1.2,x1.4,x1.7,x2.0)
                nrmenable          0 - 1 (0:off/1:on)
                moviefade          0 - 3 (0:Off,1:In,2:Out,3:InOut)
                hdmioutsize        0 - 3 (0:480,1:576,2:720,3:1080)
                panoramatype       0 - 1 (0:2D,1:3D)
                stoptype           0 - 2 (0:StateDependency ,1:NormalStop,2:ForceStop)
                moviemode          0 - 6 (0:UHD/1:UHD_D/2:FHD/3:CINEMA/4:HD/5:VGA/6:QVGA)
                startmode          0 - 1 (0:AllPath/1:PPonly)
                multiexpo          0 - 3 (0:off/1:on/2:save all/3:result only)
                stp                0 - 1 (0:off/1:on)
                dump               2 - 5 (cnt) 
                cleanout                 (stop/start)
                log              ([ldc] print)
                mvstmp             0 - 2 (0:clear/1:start/2:print)

usage: st cap live resize op1 op2 ...

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
        [lensinfo]      lens information 
        [lensproperty]  lens property information
        [reset] lens reset command
        [dis_tmout]     lens state time out disable
        [lensversion]   lens version check in sd card and body
        [ifn] [on | off]        ifn function on / off
        [ifn_en] [6]    ifn_enable degree 6
        [op_supp] [op code]     check operation support
        [ctti]  send test change_tracking_target_info op
        [backlash]      get lens backlashn

usage:  st cap lens op_supp [OpCmd] 

usage:  st cap lens wreg [data_1]
usage:  st cap lens log [param]
                * param list *
                [rxtx]
                        - level 5
                [x]
                        - level x
usage:  st cap lens sync [param] 
                [on]
                        - sync on
                [off]
                        - sync off
usage:  st cap lens oper_focus [param]
                [step]
                        - division of focus
usage:  st cap lens alt_focus [param]
usage:  st cap lens polling [param]
                [start]
                        - polling thread start
                [stop]
                        - polling thread stop
usage:  st cap lens power [param]
                        - lens power on
                        - lens is finalized

LENS IS FINALIZED.
usage:  st cap lens rport [param]
                [mount]
                        - read mount port
                [rb]
                        - read rb port
usage:  st cap lens spi [param] [param]
                [mode] [value]
                        - select mode
                [enable]
                        - spi enable
                [disable]
                        - spi disable
usage:  st cap lens wport [param] [value]
                [b2l]
                        - write b2l port
                [clk]
                        - write clk port
                [sync1]
                        - write sync1 port
                [sync2]
                        - write sync2 port
usage: st cap iq [command] [param]
                * command list *
                [af]
                        - af debug info
                [ae]
                        - ae debug info
                [awb]
                        - awb debug info
                [ipc]
                        - ipc debug info
usage: st cap iq af [command]
usage: st cap iq ipc proc [command] [param]
                [debug]
                        - set various infomation for debug
                [simul]
                        - start raw simulation
usage: st cap live log [param1] [param2]
usage: st cap live log all [on/off]
usage: st cap live log 3d [on/off]
usage: st cap live log cb [on/off]
usage: st cap live log msg [on/off]
usage: st cap live log framerate [on/off]
usage: st cap live log normal [on/off]
usage: st cap live log warnning [on/off]
usage: st cap live log error [on/off]
usage: st cap dp tmc N
usage: st cap dp tmc print
usage: st cap dp tmc mask
usage: st cap dp tmc cache
usage: st cap dp set ppu [option]
usage: st cap dp set udd [option]
usage: st cap dp set layer [grp/vid] [0/1] [on/off]
usage: st cap  [on/off]
usage: st cap dp box [draw/erase]
usage: st cap dp set evf [on/off]
usage: st cap dp set hdmi [on/off]
usage: st cap dp set hdmi size[0:FHD, 1:HD]
usage: st cap dp nrm [on/off]

usage: st gpio [command]
       st gpio help
               display help.
       st gpio dump

```
