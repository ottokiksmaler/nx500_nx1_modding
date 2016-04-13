/**
 * 
 * Simple C code to capture keypresses on NX500/NX1
 * 
 * Key events are coming from two devices /dev/event0 and /dev/event1 for top and back keys.
 * The program will capture keys and execute corresponding shell scripts from provided directory.
 * If the fourth parameter is "debug" verbose mode is turned on. File named /tmp/key_code holds name of key currently pressed
 * If the fourth parameter is "bbaf" then "True BB-AF" mode is turned on on NX1 - CAF while AF pressed, MF when not.
 * 
 * Default command line: keyscan /dev/event0 /dev/event1 /mnt/mmc/scripts/ [debug|bbaf]
 * 
 * Compile: arm-linux-gnueabihf-gcc --static -o keyscan keyscan.c -s
 * 
 */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>

#define NXKEY_EV 173
#define NXKEY_OK 96
#define NXKEY_MENU 127
#define NXKEY_PB 183
#define NXKEY_FN 172
#define NXKEY_DEL 83
#define NXKEY_UP 72
#define NXKEY_DOWN 80
#define NXKEY_LEFT 75
#define NXKEY_RIGHT 77
#define NXKEY_JOG2_CW 163
#define NXKEY_JOG2_CCW 165
#define NXKEY_JOG1_CW 177
#define NXKEY_JOG1_CCW 178
#define NXKEY_AEL 156
#define NXKEY_MOBILE 215
#define NXKEY_S1 125
#define NXKEY_S2 126
#define NXKEY_REC 171
#define NXKEY_SAS 59
#define NXKEY_SCENE 62
#define NXKEY_AUTO 64
#define NXKEY_P 65
#define NXKEY_A 66
#define NXKEY_S 67
#define NXKEY_M 68
#define NXKEY_C 71
// FOR NX1
#define NXKEY_EV1 150
#define NXKEY_C2 71 
#define NXKEY_LCD 149
#define NXKEY_JOG3_CW 105
#define NXKEY_JOG3_CCW 106
#define NXKEY_EVF 151
#define NXKEY_SS 90 // Single shot
#define NXKEY_CN 91 // Continuous normal
#define NXKEY_CH 94 // Continuous high
#define NXKEY_TIMER 97
#define NXKEY_BRACKETING 100
#define NXKEY_WB 185
#define NXKEY_ISO 186
#define NXKEY_AF 184
#define NXKEY_METERING 93
#define NXKEY_FRONT 193
#define NXKEY_AFON 188

// FOR PC DEBUG
#define NXKEY_SHIFT 42

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

int debug=0, bbaf=0, bbaf_nx500=0;
static const char *key_temp_file="/tmp/key_code";

long msec_passed(struct timeval *fromtime, struct timeval *totime)
{
  long msec;
  msec=(totime->tv_sec-fromtime->tv_sec)*1000;
  msec+=(totime->tv_usec-fromtime->tv_usec)/1000;
  return msec;
}

void create_temp_file(char *key) {
	int fd=open(key_temp_file, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd<0) printf("error opening file: %s %d\n",key_temp_file,errno);
	write(fd, key, sizeof(key));
	close(fd);
}

int main (int argc, char *argv[])
{
	// Prevent double starting the keyscan
	int pid_file = open("/tmp/keyscan.pid", O_CREAT | O_RDWR, 0666);
	if(flock(pid_file, LOCK_EX | LOCK_NB)) {
		if(EWOULDBLOCK == errno) {
			printf("Error - another %s instance already running!\n",argv[0]);
			return 255;
		}
	}
	

    char *input_device0 = NULL;
	char *input_device1 = NULL;
	char *shell_dir = NULL;
    int fd0,fd1;
	fd_set inputs;
    struct input_event ev, previous_ev = {};
	struct timeval previous_press_time;
	long msec_elapsed;
    ssize_t n;
	short unsigned int ev_pressed=0;
	char shell_name[255], shell_script[255];
	int call_shell=0;
	char *nxkeyname[256];
	int i,ready;
	
	for (i=0;i<255;i++)
		nxkeyname[i]="";
	nxkeyname[173] = "EV"; //EV key on NX500
	nxkeyname[96] = "OK";
	nxkeyname[183] = "PB";
	nxkeyname[172] = "FN";
	nxkeyname[83] = "DEL";
	nxkeyname[72] = "UP";
	nxkeyname[80] = "DOWN";
	nxkeyname[75] = "LEFT";
	nxkeyname[77] = "RIGHT";
	nxkeyname[156] = "AEL";
	nxkeyname[215] = "MOBILE";
	nxkeyname[125] = "S1";
	nxkeyname[126] = "S2";
	nxkeyname[59] = "MODE_SAS";
	nxkeyname[62] = "MODE_SCENE";
	nxkeyname[64] = "MODE_AUTO";
	nxkeyname[65] = "MODE_P";
	nxkeyname[66] = "MODE_A";
	nxkeyname[67] = "MODE_S";
	nxkeyname[68] = "MODE_M";
	nxkeyname[71] = "MODE_C"; // MODE_C1 on NX1
	nxkeyname[150] = "EV"; //EV key on NX1
	nxkeyname[70] = "MODE_C2";
	nxkeyname[149] = "TOP_LCD"; //NX top LCD backlight
	nxkeyname[151] = "EVF";
	nxkeyname[90] = "SS";
	nxkeyname[91] = "CN";
	nxkeyname[94] = "CH";
	nxkeyname[97] = "TIMER";
	nxkeyname[100] = "BRACKETING";
	nxkeyname[185] = "WB";
	nxkeyname[186] = "ISO";
	nxkeyname[184] = "AF";
	nxkeyname[93] = "METERING";
	nxkeyname[193] = "FRONT";

	nxkeyname[38] = "LK"; nxkeyname[37] = "KK";	nxkeyname[42] = "EV"; // for debugging on PC

	if (argc > 2) {
		input_device0 = argv[1];
		input_device1 = argv[2];
	} else {
		input_device0 = "/dev/input/event0";
		input_device1 = "/dev/input/event1";
	}
	
	if (argc > 3)
		shell_dir = argv[3];
	else 
		shell_dir = "/mnt/mmc/scripts/";

	if (argc > 4) {
		if (strcmp("bbaf",argv[4])==0) {
			printf("BB-AF ON\n");
			bbaf=1;
		} else {
			printf("DEBUG ON\n");
			debug=1;
		}
	}

	debug && printf("Opening inputs %s %s\n",input_device0,input_device1) && fflush(stdout);
	
    fd0 = open(input_device0, O_RDONLY);
    if (fd0 == -1) {
		debug && printf("D0 %s\n",input_device0);
        fprintf(stderr, "Error opening input file %s: %s.\n", input_device0, strerror(errno));
        return EXIT_FAILURE;
    }
    fd1 = open(input_device1, O_RDONLY);
    if (fd1 == -1) {
		debug && printf("D1 %s\n",input_device1);
        fprintf(stderr, "Error opening input file %s: %s.\n", input_device1, strerror(errno));
        return EXIT_FAILURE;
    }
    gettimeofday(&previous_press_time, NULL); 
    while (1) {
		FD_ZERO(&inputs);
		FD_SET(fd0,&inputs);
		FD_SET(fd1,&inputs);
		select(fd1+1, &inputs, NULL, NULL, NULL);
		if (FD_ISSET(fd0,&inputs))
			n = read(fd0, &ev, sizeof ev);
		else if (FD_ISSET(fd1,&inputs))
			n = read(fd1, &ev, sizeof ev);
		else continue;
		
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof ev) {
            errno = EIO;
            break;
        }
		shell_script[0]='\0';
		shell_name[0]='\0';
		call_shell=0;
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
			debug && printf("%s %d\n", evval[ev.value], (int)ev.code);
			if (debug) {
				if ((int)ev.value == 1) create_temp_file(nxkeyname[(int)ev.code]);
				if ((int)ev.value == 0) unlink(key_temp_file);
			}
			if (ev.value == 1) {
				msec_elapsed = msec_passed(&previous_ev.time,&ev.time);
			}
			if (NXKEY_EV1 != (int)ev.code && msec_elapsed < 1000 && ev.code == previous_ev.code && ev.value == previous_ev.value) {
				debug && printf("Doubleclick %s %d\n", nxkeyname[(int)ev.code], (int)ev.code);
				strncpy(shell_name,nxkeyname[(int)ev.code],8);
				strncat(shell_name,"_",8);
				strncat(shell_name,nxkeyname[(int)ev.code],8);
				call_shell=1;
			}
			if (bbaf && NXKEY_AFON == (int)ev.code && 1 == ev.value) {
				system("/usr/bin/st cap capdtm setusr AFMODE 0x70001");
			} else if (bbaf && NXKEY_AFON == (int)ev.code && 0 == ev.value) {
				system("/usr/bin/st cap capdtm setusr AFMODE 0x70003");
			}
			if (NXKEY_EV == (int)ev.code || NXKEY_EV1 == (int)ev.code || NXKEY_SHIFT == (int)ev.code) {
				if (1 == ev.value)
					ev_pressed=1;
				if (1 == ev_pressed && 0 == ev.value)
					ev_pressed=0;
			}
			if (ev_pressed == 1 && (int)ev.code != NXKEY_EV && (int)ev.code != NXKEY_SHIFT && 1 == (int)ev.value) {
				debug && printf("Combo EV + %s %d %s\n", nxkeyname[(int)ev.code], (int)ev.code, evval[(int)ev.value]);
				strncpy(shell_name,"EV_",4);
				strncat(shell_name,nxkeyname[(int)ev.code],16);
				call_shell=1;
			}
			if (ev.value == 1) {
				previous_ev = ev;
			}
			if (1 == call_shell && strlen(shell_name)>4) {
				strncpy(shell_script,shell_dir,100);
				strncat(shell_script,shell_name,16);
				strncat(shell_script,".sh",3);
				if( access( shell_script, X_OK ) != -1 ) {
					debug && printf("Executing file '%s'\n",shell_script);
					system(shell_script);
				} else {
					debug && printf("No such file '%s'\n",shell_script);
				}
			}
		}
    }
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));
    return EXIT_FAILURE;
}
