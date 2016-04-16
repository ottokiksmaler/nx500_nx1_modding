I have a feeling movie NR is one of the parameters sent to this function
UI_Mm_Camera_Set_User_Spec(int, int)

parameter 1 = 113 => set High ISO NR
parameter 1 = 114 => set long exposure NR on/off

upon record buttoin press, the following parameters are set:

parameter 1 = 0xe3, value=3
parameter 1 = 0x201, value=1
parameter 1 = 0xf1, value=1
parameter 1 = 0x10d=0
parameter 1 = 0x1f1=7
parameter 1 = 0xe4=1
parameter 1 = 0x115=0
parameter 1 = 0xd2=0
parameter 1 = 0xc9=0f
parameter 1 = 0x1d4=0
parameter 1 = 0xf6=0
parameter 1 = 0x10d=0


when recording stops:
parameter 1 = 0xe3=3
parameter 1 = 0x201=1
parameter 1 = 0xf1=0
parameter 1 = 0x10d=0
parameter 1 = 0x1f1=3
parameter 1 = 0xe4=1
parameter 1 = 0x115=0
parameter 1 = 0xd2=0
parameter 1 = 0xc9=0f
parameter 1 = 0x1d4=0
parameter 1 = 0xf6=0
parameter 1 = 0xee=0
parameter 1 = 0xf4=1
