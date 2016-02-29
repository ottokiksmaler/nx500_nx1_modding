#Working with key events

As these cameras run Linux working with keys is quite normal. Only differences are two keyboards (top face / back face) and non-standard keys (obviously).

Output of xinput list:
```
⎡ Virtual core pointer                        id=2    [master pointer  (3)]
⎜   ↳ Virtual core XTEST pointer                    id=4    [slave  pointer  (2)]
⎜   ↳ Touchscreen                                   id=7    [slave  pointer  (2)]
⎣ Virtual core keyboard                       id=3    [master keyboard (2)]
    ↳ Virtual core XTEST keyboard                     id=5    [slave  keyboard (3)]
    ↳ Drime5 ADC Keyboard                             id=6    [slave  keyboard (3)]
    ↳ Drime5 GPIO Keyboard                            id=8    [slave  keyboard (3)]
∼ Touchscreen subdev 1                        id=9    [floating slave]
```
Output of "xinput test 6":
```
EV - 181
MENU - 135
REC - 179
Fn - 180
PB - 191
DEL - 91
OK - 104
LEFT - 83
UP - 80
RIGHT - 85
DOWN - 88
MODE_DIAL_SAS - 67
MODE_DIAL_S - 70
MODE_DIAL_AUTO - 72
MODE_DIAL_P - 73
MODE_DIAL_A - 74
MODE_DIAL_S - 75
MODE_DIAL_M - 76
MODE_DIAL_C - 79
```
I guess that NX1 should have C1/C2 at 77/78. NX500 actually has **two** Custom Modes supported. They can be accessed by simulating mode dial operations by using **st key** command.

Output of "xinput test 8":
```
JOG1_CW - 185
JOG1_CCW - 186
JOG2_CW - 171
JOG2_CCW - 173
AEL - 164
S1 - 133
S2 - 134
MOBILE - 233
```
CW and CCW roughly mean to left and to right (as it's arbitraty on the back wheel).

###Generating key and touch events

You can use **st key** for simulating pressing, releasing and clicking, like this:
```
st key click OK
st key press S1
st key click S2
st key release S1
st key jog jog1_cw
st key touch click 300 300 
st key touch push 200 200 
st key touch release 400 300 
```

###Recording key events

xinput works for trying things out.
Keyboards are accessible via standard /dev/input/event* access, just like in any other Linux.
