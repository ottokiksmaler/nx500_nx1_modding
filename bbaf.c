/**
 * 
 * Compile: arm-linux-gnueabi-gcc -o bbaf bbaf.c -s  --sysroot=../arm/ -Wl,-dynamic-linker,/lib/ld-2.13.so
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

static char *version_model, *version_release;
static int debug=1, i=0;

int di_message_send(char * message_in){
	unsigned char message_text[208]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	unsigned char *param, *message, *spl;
	int i=0, result, di_message_queue_id=0;
	struct msg_buf_out {
		long mtype;
		char mtext[208];
	} msg;
	if (message_in[0]=='/')
		asprintf(&message,"%s",message_in);
	else
		asprintf(&message,"/usr/bin/st %s",message_in);
	
	spl=strtok(message," ");
	
	while(spl && strlen(spl)>0) {
		asprintf(&param,"%s",spl);
		if (debug==2) printf("Adding at %d %s(%d)\n",4+i*20,param,(int)strlen(param));
		memcpy(message_text+4+i*20,param, strlen(param));
		i++;
		spl = strtok(NULL, " ");
	}
	asprintf(&param,"%d",i);
	memcpy(message_text,param, strlen(param));

	if (debug==2) {
		printf("Message:\n");
		for(i=0;i<208;i++) {
			if ((i-4)%20==0) printf("\n");
			if (message_text[i]==0) 
				printf("_"); 
			else 
				printf("%c",(char)message_text[i]);
		}
		printf("\n");
	}

	if (di_message_queue_id<1) {
		di_message_queue_id = msgget(0x8828, 0666);
		if (di_message_queue_id<0) {
			perror(strerror(errno));
			printf("ERROR %d %d\n",errno, di_message_queue_id);
			return -1;
		}
	}
	msg.mtype=1;
	memcpy(msg.mtext, message_text, 208);
	result = msgsnd(di_message_queue_id, &msg, 208, 0);
	if (result<0) {
		perror( strerror(errno) );
		return -1;
	}
	return result;
}

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

int main (int argc, char *argv[])
{
	// Prevent double starting the bbaf. If the lock file is stale - remove/reinsert battery // TODO
	int pid_file = open("/tmp/bbaf.pid", O_CREAT | O_RDWR, 0666);
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
	printf("Running bbaf on %s v %s\n",version_model, version_release);
	
	for (i=1;i<argc;i++) {
		if (0==strcmp(argv[i],"debug")) {
			printf("DEBUG ON\n");
			debug = 1;
		}
	}

    int fd0,fd1;
	fd_set inputs;
	size_t n;
	struct input_event ev;
	
    fd0 = open("/dev/input/event0", O_RDONLY);
    if (fd0 == -1) {
        fprintf(stderr, "Error opening input file %s: %s.\n", "/dev/input/event0", strerror(errno));
        return EXIT_FAILURE;
    }
    fd1 = open("/dev/input/event1", O_RDONLY);
    if (fd1 == -1) {
        fprintf(stderr, "Error opening input file %s: %s.\n", "/dev/input/event1", strerror(errno));
        return EXIT_FAILURE;
    }
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
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
			debug && printf("%s %d\n", evval[ev.value], (int)ev.code);
			if (NXKEY_AFON==(int)ev.code){
				if (0==ev.value) {
					if(debug) printf("AF-ON RELEASED\n");
					di_message_send("app nx key single ael");
				}
				if (1==ev.value) {
					if(debug) printf("AF-ON PRESSED\n");
					di_message_send("app nx key single ael");
				}
			}
		}
    }
    fflush(stdout);
    fprintf(stderr, "Error: %s.\n", strerror(errno));
	close(pid_file);
    return EXIT_FAILURE;
}
