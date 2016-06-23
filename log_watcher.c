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

#define PROGRAM "log_watcher"
#define VERSION "0.2"
#define BUFF_SIZE 1024

#define GENGRID_CHECK_ITEM 1
#define GENGRID_UNCHECK_ITEM 2
#define ENTRIES_MAX 1024
static char *entries[ENTRIES_MAX];

static char *version_model, *version_release, *current_open_file="", *current_video_mode="1920x1080@120.000000";
static int pid_file, debug=0, debug_all=0, max_video_seconds=4500, video_seconds_grace=10, video_seconds_delay=2;
double fps=30.0,max_video_frames=215000.0, current_frame=0.0;

static void entries_init(){
	int i;
	for (i=0;i<ENTRIES_MAX;i++) asprintf(&entries[i],"%s","");
}
static void entry_add(char *entry){
	int i;
	for(i=0;i<ENTRIES_MAX;i++)
		if(strcmp(entries[i],entry)==0)
			return;
	for(i=0;i<ENTRIES_MAX;i++)
		if(strlen(entries[i])==0) 
			if (asprintf(&entries[i],"%s",entry)>-1) return;
	return;
}
static void entry_remove(char *entry){
	int i;
	for(i=0;i<ENTRIES_MAX;i++)
		if(strcmp(entries[i],entry)==0)
			if (asprintf(&entries[i],"%s","")>-1) return;
	return;
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


int execute_script(char * script_name) {
	debug && printf("Executing: %s\n",script_name);
	return system(script_name);
}

void buffer_clean(char buffer_in[BUFF_SIZE], char buffer_out[BUFF_SIZE], int n) {
	int i,j=0;
	for(i=0;i<n;i++) {
		if (buffer_in[i]>=32 && buffer_in[i]<=127) {
			buffer_out[j]=buffer_in[i];
			j++;
		}
	}
	buffer_out[j]=0;
}

long msec_passed(struct timeval *fromtime, struct timeval *totime)
{
  long msec;
  msec=(totime->tv_sec-fromtime->tv_sec)*1000;
  msec+=(totime->tv_usec-fromtime->tv_usec)/1000;
  return msec;
}

void sig_handler(int signo)
{
  FILE *fp;
  if (signo == SIGINT){
	  close(pid_file);
	  printf("Exiting ...\n");
	  exit(0);
  }
  if (signo == SIGUSR1){
	fp = fopen("/tmp/log_watcher_current_open_file", "w");
	if (fp) {
		fprintf(fp,"%s",current_open_file);
		fclose(fp);
	}
	fp = fopen("/tmp/log_watcher_selected_files", "w");
	int i,first=1;
	if (fp) {
		for(i=0;i<ENTRIES_MAX;i++) {
			if (strlen(entries[i])>0) {
				if (0==first) {
					fprintf(fp,",%s",entries[i]);
					if (debug) printf("%s\n",entries[i]);
				} else {
					fprintf(fp,"%s",entries[i]);
					first=0;
					if (debug) printf("%s\n",entries[i]);
				}
			}
		}
		fclose(fp);
	}
  }
}

int main (int argc, char *argv[])
{
	// Prevent double starting. If the lock file is stale - remove/reinsert battery // TODO
	pid_file = open("/tmp/log_watcher.pid", O_CREAT | O_RDWR, 0666);
	int old_pid;
	char *video_resolution, *video_fps;
	
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
	printf("Running %s %s on %s v %s\n",argv[0],VERSION, version_model, version_release);

	char buffer[BUFF_SIZE], buffer_out[BUFF_SIZE];
	char *log_file = NULL;
	char *current_file_file="/tmp/logwatch_current_file";
	char *command;
    int fd, current_action=0, read_all=0;
	ssize_t n;
	struct timeval previous_read_time, current_read_time;
	long msec_elapsed, video_seconds=0;
	unsigned int param_int=0;

	if (signal(SIGUSR1, sig_handler) == SIG_ERR)
		printf("ERROR: Unable to catch SIGUSR1!\n");
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		printf("ERROR: Unable to catch SIGINT!\n");
  
	log_file = "/dev/log_main";
	if (argc > 1) {
		if (strcmp("help",argv[1])==0) {
			printf("Tool to restart video after set number of seconds or frames.\n\n");
			printf("Usage:\n\t%s help - show this help\n\t%s [max_seconds] [max_frames] [debug|debug_all] - default 4500 s and 215000 frames\n\n",argv[0],argv[0]);
			printf("This tool also monitors selected files in gallery and creates a file with selected filenames when sent USR1 signal:\n/tmp/log_watcher_current_open_file - with the filename of currently displayed file\n/tmp/log_watcher_selected_files - comma separated filenames of selected files.\n\n");
			exit(0);
		}
		if (argc>1 && sscanf(argv[1],"%d",&param_int)) max_video_seconds=param_int;
		if (argc>2 && sscanf(argv[2],"%d",&param_int)) max_video_frames=(double)param_int;
		if (strcmp("debug",argv[argc-1])==0)  {
			debug=1;
			printf("Debug ON\n");
		}
		if (strcmp("debug_all",argv[argc-1])==0)  {
			debug=1;
			debug_all=1;
			printf("Debug_all ON\n");
		}
	}
	
    fd = open(log_file, O_RDONLY);
    if (fd == -1) {
		debug && printf("D1 %s\n",log_file);
        fprintf(stderr, "Error opening input %s: %s.\n", log_file, strerror(errno));
        return EXIT_FAILURE;
    }

    entries_init();
    while(1) {
		gettimeofday(&previous_read_time, NULL); 
		while ((n=read(fd,buffer,BUFF_SIZE))>0){
			if (read_all==0) gettimeofday(&current_read_time, NULL);
			if (read_all==1 || msec_passed(&previous_read_time,&current_read_time)>100) read_all=1;
			if (read_all==0) continue;
			buffer[n]=0;
			if (n>16) {
				buffer_clean(buffer,buffer_out,n);
				if (debug_all) printf("%s\n", buffer_out);
				if (strstr(buffer_out,"UI_PB_Thumbnail_Destruct")!=NULL){
					entries_init();
					if (debug) printf("Exiting thumbnail playback mode\n");
				}
				if (strstr(buffer_out,"GENGRID_CHECK_ITEM")!=NULL) current_action=GENGRID_CHECK_ITEM;
				if (strstr(buffer_out,"GENGRID_UNCHECK_ITEM")!=NULL) current_action=GENGRID_UNCHECK_ITEM;
				if (strstr(buffer_out,"[mfilepath - ")!=NULL){
					strncpy(buffer, strstr(buffer_out,"[mfilepath - ")+13,BUFF_SIZE);
					buffer[strlen(buffer)-2]=0;
					if (debug) printf("%d:%s\n",current_action, buffer);
					if (current_action==GENGRID_CHECK_ITEM) entry_add((char *)buffer);
					if (current_action==GENGRID_UNCHECK_ITEM) entry_remove((char *)buffer);
				}
				if (strstr(buffer_out,"__display_file")!=NULL){
					strncpy(buffer, strstr(buffer_out,"path[")+5,BUFF_SIZE);
					buffer[strstr(buffer,"]")-buffer]=0;
					if (debug) printf("Display:%s\n",buffer);
				}
				if (strstr(buffer_out,"__ui_cb_recording_status")!=NULL){
					strncpy(buffer, strstr(buffer_out," > [m")+5,BUFF_SIZE);
					buffer[strstr(buffer,"/")-buffer]=0;
					video_seconds = strtol(buffer, NULL, 10);
					if (fps>0) current_frame = video_seconds * fps; else current_frame = 0.0;
					if (video_seconds==max_video_seconds || video_seconds>(max_video_seconds+video_seconds_grace) || current_frame > max_video_frames) {
						asprintf(&command,"st key click rec && sleep %d && st key click rec", video_seconds_delay);
						execute_script(command);
					}
					if (debug) printf("Seconds: %ld\n",video_seconds);
				}
				if (strstr(buffer_out,"TYPE 0: movResolution: ")!=NULL){
					strncpy(buffer, strstr(buffer_out,"TYPE 0: movResolution: ")+strlen("TYPE 0: movResolution: "),BUFF_SIZE);
					buffer[strstr(buffer," ")-buffer]=0;
					if (debug) printf("Video mode:%s\n",buffer);
					asprintf(&current_video_mode,"%s",buffer);
					video_resolution=strtok(current_video_mode,"@");
					video_fps=strtok(NULL," ");
					sscanf(video_fps,"%lf",&fps);
				}
				if (strstr(buffer_out,"GetCurrent called m_strURI = ")!=NULL){
					strncpy(buffer, strstr(buffer_out,"/mnt/mmc"),BUFF_SIZE);
					buffer[strstr(buffer," ")-buffer]=0;
					if (debug) printf("Current:%s\n",buffer);
					asprintf(&current_open_file,"%s",buffer);
				}
			}
		}
	}
}