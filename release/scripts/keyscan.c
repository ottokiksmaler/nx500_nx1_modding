/**
 * 
 * Simple C code to capture keypresses on NX500/NX1
 * 
 * Key events are coming from two devices /dev/event0 and /dev/event1 for top and back keys.
 * The program will capture keys and execute corresponding shell scripts from provided directory.
 * If the fourth parameter is "debug" verbose mode is turned on. File named /tmp/key_code holds name of key currently pressed
 * If the fourth parameter is "bbaf" then "True BB-AF" mode is turned on on NX1 - CAF while AF pressed, MF when not.
 * 
 * keyscan will try to execute files by {scripts}/auto/*.sh in order they are found in upon star or restart (wake up)
 * 
 * If there is no /mnt/mmc/scripts directory it will try to use /opt/usr/devel/scripts directory.
 * 
 * Default command line: keyscan /dev/event0 /dev/event1 /mnt/mmc/scripts/ [debug|bbaf]
 * 
 * Compile: arm-linux-gnueabi-gcc --static -o keyscan keyscan.c -lpthread -s
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
#include <signal.h>
#include <pthread.h>
#include <glob.h>

#define timer_sleep 1 // time in seconds to detect sleep events

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

int debug=0, bbaf=0, bbaf_nx500=0, running_from_card=0, persistent_peaking=0;
static const char *key_temp_file="/tmp/key_code"; // file to store current key name in debugging
static const char *opt_scripts_dir="/opt/usr/devel/scripts/"; // default scripts directory if none found on SD card
static char *scripts_dir;
static char *version_model, *version_release;

pthread_t timer_thread, cleanup_thread;

long int pref_get_long(int a, int prefno);

static int version_load()
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0, i = 0;
	ssize_t read;

	fp = fopen("/etc/version.info", "r");
	if (fp != NULL) {
		if ((read = getline(&line, &len, fp)) != -1) {
			line[strcspn(line, "\r\n")] = 0;
			asprintf(&version_release, "%s", line);
		}
		if ((read = getline(&line, &len, fp)) != -1) {
			line[strcspn(line, "\r\n")] = 0;
			asprintf(&version_model, "%s", line);
		}
		fclose(fp);
		free(line);
		return 0;
	}
	printf("Unable to determine device model and firmware version!\n");
	return -1;
}


int execute_script(char * script_name) {
	debug && printf("Executing: %s\n",script_name);
	return system(script_name);
}

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

/* auto_run_process
 * 
 * Executes scripts from {scripts}/auto/*.sh 
 * 
 * Sleeps 2s for scripts on SD card
 * 
 */
void auto_run_process() {
	char *auto_dir, *command;
	int i;
	debug && printf("Executing auto scripts\n");
	asprintf(&auto_dir,"%s/auto/*.sh",scripts_dir);
	// need some time for files to become accessible on SD card
	if (strstr(auto_dir,"mmc") || strstr(auto_dir,"sdcard")) {
		sleep(2);
	}
	// blink SD card led on back to indicate auto running scripts
	for (i=0;i<3*debug;i++)
		execute_script("echo 1 > /sys/devices/platform/leds-gpio/leds/card/brightness;sleep 0.2;echo 0 > /sys/devices/platform/leds-gpio/leds/card/brightness; sleep 0.1");
	glob_t globbuf;
	if (GLOB_NOMATCH != glob( auto_dir, 0, NULL, &globbuf)) {
		for( i = 0; i < globbuf.gl_pathc; i++ ) {
			asprintf(&command, "/opt/usr/devel/scripts/popup_timeout \"X: %s\" 1", globbuf.gl_pathv[i]);
			//debug && system(command);
			execute_script(globbuf.gl_pathv[i]);
		}
	}
	if( globbuf.gl_pathc > 0 )
		globfree( &globbuf );
	
}

// Detect sleep events
void* timer_loop(void* arg) {
	struct timeval previous_time_loop, current_time_loop;
	long msec_elapsed;
	while(1) {
		gettimeofday(&previous_time_loop, NULL); 
		sleep(timer_sleep);
		gettimeofday(&current_time_loop, NULL); 
		msec_elapsed = msec_passed(&previous_time_loop,&current_time_loop);
		if (msec_elapsed>(timer_sleep*1000+300)) auto_run_process();
	}
}

int main (int argc, char *argv[])
{
	// Prevent double starting the keyscan. If the lock file is stale - remove/reinsert battery // TODO
	int pid_file = open("/tmp/keyscan.pid", O_CREAT | O_RDWR, 0666);
	int old_pid;
	if (pid_file) {
		if(flock(pid_file, LOCK_EX | LOCK_NB)) {
			read(pid_file, &old_pid, sizeof(old_pid));
			printf("OLD PID: %d\n",old_pid);
			if(EWOULDBLOCK == errno) {
				printf("Error - another %s instance already running!\n",argv[0]);
				return 255;
			}
			printf("Error locking the pid file: %d\n",errno);
			return errno;
		}
		int pid=(int)getpid();
		printf("PID: %d\n",pid);
		write(pid_file,&pid, sizeof(pid));
		fsync(pid_file);
	} else {
		printf("Unable to create PID file.\n");
		return 255;
	}

	version_load();
	printf("Running keyscan on %s v %s\n",version_model, version_release);
	// if running from card no need for sleep detect - keyscan is killed on sleep
	if (strstr(argv[0],"mmc") || strstr(argv[0],"sdcard")) {
		running_from_card=1;
	}
	if(0 == running_from_card)
		pthread_create(&timer_thread, NULL, &timer_loop, NULL);
	
    char *input_device0 = NULL;
	char *input_device1 = NULL;
    int fd0,fd1;
	fd_set inputs;
    struct input_event ev, previous_ev = {};
	struct timeval previous_press_time;
	long msec_elapsed;
    ssize_t n;
	short unsigned int ev_pressed=0;
	char shell_name[255], shell_script[255], opt_shell_script[255];
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

	for (i=1;i<argc;i++) {
		if (0==strcmp(argv[i],"peaking")) {
			printf("Persistent peaking ON\n");
			persistent_peaking=1;
		}
		if (0==strcmp(argv[i],"debug")) {
			printf("DEBUG ON\n");
			debug = 1;
		}

		if (0==strcmp(argv[i],"bbaf")) {
			printf("BB-AF ON\n");
			bbaf=1;
		}
	}
	

	if (argc > 2) {
		input_device0 = argv[1];
		input_device1 = argv[2];
	} else {
		input_device0 = "/dev/input/event0";
		input_device1 = "/dev/input/event1";
	}
	
	if (argc > 3)
		scripts_dir = argv[3];
	else
		scripts_dir = "/mnt/mmc/scripts/";
	
	if (0 != access(scripts_dir,X_OK)) {
		if (0 == access(opt_scripts_dir,X_OK)) {
			asprintf(scripts_dir,"%s",opt_scripts_dir);
		} else {
			printf("Invalid scripts directory: %s\nExiting the program...\n",scripts_dir);
			exit(255);
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
	// TODO should we identify mods?
	//system("/opt/usr/devel/scripts/popup_timeout '  NX-MOD v2.0  ' 1");
    auto_run_process(); // execute all automatic scripts on first start
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
				sprintf(shell_name,"%s_%s",nxkeyname[(int)ev.code],nxkeyname[(int)ev.code]);
				call_shell=1;
			}
			if (bbaf && NXKEY_AFON == (int)ev.code && 1 == ev.value) {
				execute_script("/usr/bin/st cap capdtm setusr AFMODE 0x70001");
			} else if (bbaf && NXKEY_AFON == (int)ev.code && 0 == ev.value) {
				execute_script("/usr/bin/st cap capdtm setusr AFMODE 0x70003");
			}
			if (1==persistent_peaking && 0==ev_pressed && NXKEY_S1==(int)ev.code && 0==ev.value && 0 == access("/tmp/peaking_on",R_OK)){
				execute_script("/usr/bin/st key click ok & ");
			}
			if (NXKEY_EV == (int)ev.code || NXKEY_EV1 == (int)ev.code || NXKEY_SHIFT == (int)ev.code) {
				if (1 == ev.value)
					ev_pressed=1;
				if (0 == ev.value)
					ev_pressed=0;
			}
			if (ev_pressed == 1 && (int)ev.code != NXKEY_EV && (int)ev.code != NXKEY_SHIFT && 1 == (int)ev.value) {
				ev_pressed=0;
				debug && printf("Combo EV + %s %d %s\n", nxkeyname[(int)ev.code], (int)ev.code, evval[(int)ev.value]);
				sprintf(shell_name,"EV_%s",nxkeyname[(int)ev.code]);
				call_shell=1;
			}
			if (ev.value == 1) {
				previous_ev = ev;
			}
			if (1 == call_shell && strlen(shell_name)>4) {
				sprintf(shell_script,"%s/%s.sh",scripts_dir,shell_name);
				if( access( shell_script, X_OK ) != -1 ) {
					execute_script(shell_script);
				} else {
					sprintf(opt_shell_script,"%s/%s.sh",opt_scripts_dir,shell_name);
					if( access( opt_shell_script, X_OK ) != -1 ) {
						execute_script(opt_shell_script);
					} else {
						debug && printf("No such file '%s' or '%s'\n",shell_script,opt_shell_script);
					}
				}
			}
		}
    }
    fflush(stdout);
    fprintf(stderr, "Error: %s.\n", strerror(errno));
	close(pid_file);
    return EXIT_FAILURE;
}
