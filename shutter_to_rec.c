#include <unistd.h>
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

static FILE *fp;
static int fd0, debug=1;
static char *version_model, *version_release;

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

int unmask_shutter() {
	unsigned char keymask_clean[] = {
	0x30, 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x0a
	};
	unsigned int keymask_clean_len = 11;
	fp=fopen("/sys/devices/platform/d5-keys/keymask", "w");
	if (fp) {
		fwrite(keymask_clean, 1, keymask_clean_len, fp);
		fclose(fp);
	}
}

int mask_shutter() {
	unsigned char keymask_masked[] = {
	0x30, 0x78, 0x30, 0x30, 0x30, 0x30, 0x31, 0x38, 0x30, 0x30, 0x0a
	};
	unsigned int keymask_masked_len = 11;
	fp=fopen("/sys/devices/platform/d5-keys/keymask", "w");
	if (fp) {
		fwrite(keymask_masked, 1, keymask_masked_len, fp);
		fclose(fp);
	}
}

void sig_handler(int signo)
{
	printf("Exiting ...\n");
	unmask_shutter();
	exit(0);
}

int main (int argc, char *argv[])
{
	char buffer[11];
	char *pushed_keys;
	fd_set inputs;
	int n, s1, s2, old_s1=0, old_s2=0;

	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("ERROR: Unable to catch SIGUSR1!\n");
	
	version_load();
	printf("Running shutter_to_rec on %s v %s\n",version_model, version_release);
	
	if (strcmp("NX500",version_model)==0){
		asprintf(&pushed_keys,"%s","/sys/devices/platform/d5-keys/pushed_keys");
	} else {
		asprintf(&pushed_keys,"%s","/sys/devices/platform/d5-keys/pushed_keys");
	}
	mask_shutter();
	debug && printf("Opening %s\n",pushed_keys);
    while (1) {
		fd0 = open(pushed_keys, O_RDONLY);
		if (fd0 == -1) {
			fprintf(stderr, "Error opening input file %s: %s.\n", pushed_keys, strerror(errno));
			return EXIT_FAILURE;
		}
		n = read(fd0, &buffer, 11);
		close(fd0);
		s1 = (buffer[7] & 8) > 0;
		s2 = (buffer[6] & 1) > 0;
		if (old_s2 != s2) {
			if (debug) printf("S1: %d\tS2: %d\n", s1, s2);
			if (old_s2 == 0 && s2 == 1) system("st key click rec");
		}
		old_s1=s1;
		old_s2=s2;
		usleep(100000); // TODO implement inotify approach
	}
	unmask_shutter();
}