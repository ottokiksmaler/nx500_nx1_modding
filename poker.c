/*
 * Change memory of another process 4 bytes at a time :)
 * 
 * Usage: ./poker <PID> <hex_address:hexpair_value[:hexpair_value_original]>
 * Example:
 * ./poker 247 0x00400658:45464748 - changes 4 bytes to 'EFGH' at address 0x00400658' of PID 247
 * 
 * Example:
 * ./poker 247 0x00400658:45464748:42424242 - changes 'AAAA' to 'EFGH' at address 0x00400658' of PID 247 only if original bytes were 'AAAA'
 * 
 * Compile with
 * arm-linux-gnueabihf-gcc --static -o poker poker.c --sysroot=../arm/ -Wl,-dynamic-linker,/lib/ld-2.13.s
 */

#include <strings.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFF_SIZE 255

static bool debug = false;
static bool debug_errors = true;

int pid_attach(pid_t pid)
{
	unsigned char dev_mem_filename[BUFF_SIZE];
	debug && printf("ATTACH PID: %d\n",(int)pid);
	sprintf(dev_mem_filename, "/proc/%d/mem", pid);
	int fd = open(dev_mem_filename, O_RDWR);
	if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
		(debug || debug_errors) && printf("Open(%s): ERROR\n", dev_mem_filename);
		return false;
	}
	if (waitpid(pid, NULL, 0) == -1) {
		(debug || debug_errors) && printf("waitpid(%d): ERROR\n", (int)pid);
		ptrace(PTRACE_DETACH, pid, NULL, NULL);
		return false;
	}
	return fd;
}

int pid_detach(pid_t pid)
{
	ptrace(PTRACE_DETACH, pid, NULL, NULL);
	debug && printf("Detach PID %d: OK\n",(int)pid);
}

bool peek(int fd, off_t offset, unsigned char *buffer, size_t size)
{
	if (size>BUFF_SIZE) {
		(debug || debug_errors) && printf("SIZE TOO LARGE ERROR %d > %d\n", (int)size, BUFF_SIZE);
		return false;
	}
	int i=0;
	if (lseek(fd, (off_t) offset, SEEK_SET))
		if (read(fd, buffer, size) >= 0)
			debug && printf("Peek: OK %d\n", i);
		else {
			(debug || debug_errors) && printf("Error peek: %d\n", (errno));
			return false;
		}
	return true;
}

bool poke(int fd, off_t offset, unsigned char *buffer, size_t size)
{
	if (size>BUFF_SIZE) {
		(debug || debug_errors) && printf("SIZE TOO LARGE ERROR %d > %d\n", (int)size, BUFF_SIZE);
		return false;
	}
	int i=0;
	if (lseek(fd, (off_t) offset, SEEK_SET))
		if (i = write(fd, buffer, size) >= 0){
			debug && printf("OK poke %d\n", i);
		}
		else {
			(debug || debug_errors) && printf("Error poke: %d\n", (errno));
			return false;
		}
	return true;
}

bool pokeif(int fd, off_t offset, unsigned char *buffer_original, unsigned char *buffer, size_t size)
{
	if (size>BUFF_SIZE) {
		(debug || debug_errors) && printf("SIZE TOO LARGE ERROR %d > %d\n", (int)size, BUFF_SIZE);
		return false;
	}
	unsigned char buffer_temp[BUFF_SIZE];
	if (!peek(fd, offset, buffer_temp,4)) {
		return false;
	}
	int i=0;
	for (i=0;i<size;i++) {
		if (buffer_temp[i] != buffer_original[i]) {
			(debug || debug_errors) && printf("Buffers not the same: ERROR\n");
			return false;
		}
	}
	if (!poke(fd, offset, buffer,4)) {
		return false;
	}
	return true;
}

void hex_to_char_array(unsigned char *hex, unsigned char * buffer)
{
	int i;
	for(i = 0; i < 4; i++) {
        sscanf(hex, "%2hhx", &buffer[i]);
        hex += 2;
    }
}

int main(int argc, unsigned char *argv[])
{
	int fd,i,b;
	pid_t pid;
	off_t offset;
	unsigned char arg[BUFF_SIZE], buff_old[4], buff_new[4];
	unsigned char *spl;
	
	if (argc < 3) {
		printf("\nUsage: %s <PID> <hex_address:hexpair_value[:hexpair_value_original]>\n\nExample:\n%s 247 0x00400658:45464748 - changes 4 bytes to 'EFGH' at address 0x00400658' of PID 247\n\nExample:\n%s 247 0x00400658:45464748:42424242 - changes 'AAAA' to 'EFGH' at address 0x00400658' of PID 247 only if original bytes were 'AAAA'\n\n",argv[0],argv[0],argv[0]);
		return 1;
	}
	pid = atoi(argv[1]);
	if (pid==0){
		printf("Invalid PID: %d\n",pid);
		return 1;
	}
	spl=malloc(BUFF_SIZE*sizeof(char));
	fd = pid_attach(pid);
	if (fd>0) {
		for (i=2;i<argc;i++) {
			debug && printf("ARG %d %s\n",i,argv[i]);
			strncpy(arg,argv[i],32);
			spl = strtok(arg, ":");
			offset = strtol(spl, NULL, 16);
			spl = strtok(NULL, ":");
			hex_to_char_array(spl,buff_new);
			spl = strtok(NULL, ":");
			if (spl) {
				hex_to_char_array(spl,buff_old);
				if(!pokeif(fd, offset, buff_old, buff_new, 4))
					return 1;
			} else {
				if(!poke(fd, offset, buff_new, 4))
					return 1;
			}
		}
	} else {
		return 1;
	}
	pid_detach(pid);
	return 0;
}
