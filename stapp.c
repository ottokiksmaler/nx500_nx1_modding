/*
 * Fast "st app" alternative
 * Compile with 
 * arm-linux-gnueabi-gcc -o stapp stapp.c --sysroot=../arm/ -Wl,-dynamic-linker,/lib/ld-2.13.so
 * 
 */
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static int fd=0, debug=1;

int send_message(char * message_in){
	int i=0, result;
	unsigned char message_text[208]="\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
//	unsigned char message_text[208]="\0\0\0\0/usr/bin/st\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	unsigned char *param, *message, *spl;
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
		if (debug) printf("Adding at %d %s(%d)\n",4+i*20,param,(int)strlen(param));
		memcpy(message_text+4+i*20,param, strlen(param));
		i++;
		spl = strtok(NULL, " ");
	}
	asprintf(&param,"%d",i);
	memcpy(message_text,param, strlen(param));

	if (debug) {
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

int send_message_array(int num, ...) {
	va_list valist;
	int i, result;
	char message_text[208]="\0\0\0\0/usr/bin/st\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
	char * param;
	struct msg_buf_out {
		long mtype;
		char mtext[208];
	} msg;
	
	va_start(valist, num);
	asprintf(&param,"%d",num+1);
	memcpy(message_text,param, strlen(param));
	
	for (i = 0; i < num; i++) {
		asprintf(&param,"%s",va_arg(valist, char *));
		if (debug) printf("Adding at %d %s(%d)\n",4+(i+1)*20,param,(int)strlen(param));
		memcpy(message_text+4+(i+1)*20,param, strlen(param));
	}
	if (debug) {
		printf("Message:\n");
		for(i=0;i<208;i++) {
// 			if ((i-4)%20==0) printf("\n");
			if (message_text[i]==0) 
				printf("_"); 
			else 
				printf("%c",(char)message_text[i]);
		}
		printf("\n");
	}
	va_end(valist);
	msg.mtype=1;
	memcpy(msg.mtext, message_text, 208);
	result = msgsnd(fd, &msg, 208, 0);
	if (result<0) {
		perror( strerror(errno) );
		return -1;
	}
	return result;
}

int main (int argc, char *argv[])
{
	if (argc>1 && strlen(argv[1])>1) return send_message(argv[1]);
}