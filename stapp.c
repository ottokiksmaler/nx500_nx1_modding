/*
* Usage: 
* 
* 
* Compile with:
*  
* arm-linux-gnueabi-gcc -o stapp stapp.c --sysroot=../arm/ -Wl,-dynamic-linker,/lib/ld-2.13.so
* We need to specify the correct ld or it will not work on device.
*/
#define _GNU_SOURCE
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

// default debug
static int debug=0;

static void run_command(char *command)
{
	if (debug) printf("CMD: %s", command);
	char *cmd;
	asprintf(&cmd, "%s", command);
	system(cmd);
	free(cmd);
	if (debug) printf(" done.\n");
}

int send_message(char * message_in){
	int i=0, result, fd=-1;
	unsigned char message_text[208]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	char  *param, *message, *spl;
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
		if (debug>2) printf("Adding at %d %s(%d)\n",4+i*20,spl,(int)strlen(spl));
		memcpy(message_text+4+i*20,spl,strlen(spl));
		i++;
		spl = strtok(NULL, " ");
	}
	asprintf(&spl,"%d",i);
	memcpy(message_text,spl, strlen(spl));

	if (debug>1) {
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

	if (fd<1) {
		fd = msgget(0x8828, 0666);
		if (fd<0) {
			perror(strerror(errno));
			printf("ERROR %d %d\n",errno, fd);
			return -1;
		}
	}
	msg.mtype=1;
	memcpy(msg.mtext, message_text, 208);
	result = msgsnd(fd, &msg, 208, 0);
	if (result<0) {
		perror( strerror(errno) );
		return -1;
	}
	return result;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		run_command("/usr/bin/st");
		return 1;
	}
	if (argc >= 3 && strcmp(argv[argc - 1], "debug") == 0) {
		debug = 3;
	}
	if (debug) printf("Debug ON\n");

	send_message(argv[1]);
	return 0;
}
