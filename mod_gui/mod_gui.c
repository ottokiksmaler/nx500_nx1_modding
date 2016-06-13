/*
* Usage: 
* 
* mod_gui path_to_scripts_folder_or_config_file
* 
* mod_gui will search for either (MODEL = NX1 or NX500):
* 1) mod_gui.cfg.MODEL if given a scripts directory 
* 2) config_file.MODEL if given a config filename, scripts directory is dir containing the config file
* 
* # A comment
* <checkbox|button>|<Label text 1>|<script_to_run1.sh>
* <checkbox|button>|<Label text 2>|<script_to_run2.sh>
* 
* <checkbox|button>|<Label text X>|<script_to_runX.sh>
* button|<Label text Y|@config_file_for_sub_menu.cfg
* 
* Checkboxes upon activation and after executing the script, copy the script file to "auto" directory for keyscan to run upon start
* Buttons just run the script 
* If command starts with @ then it's used as a configuration file for sub-menu that is shown by clicking the button
* MENU closes the application
* 
* Compile with:
*  
* arm-linux-gnueabi-gcc -s -o mod_gui mod_gui.c `pkg-config --cflags --libs ecore elementary` -lecore_input --sysroot=../arm/ -Wl,-dynamic-linker,/lib/ld-2.13.so
* We need to specify the correct ld or it will not work on device.
*/
#define _GNU_SOURCE
#include <Ecore.h>
#include <Ecore_Input.h>
#include <Elementary.h>
#include <strings.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480
#define MAX_BUTTONS 24
#define MAX_PAGES 16
int debug = 0;

static Evas_Object *win, *bg, *bg2, *box, *btn, *chk, *table;

char *version_model, *version_release, *configuration_file;
int button_height = 80, button_width = 360, button_number = 0;

static Eina_Bool chk_value[MAX_BUTTONS];
static int datas[16];
static char *scripts;
static char *button_type[MAX_BUTTONS];
static char *button_name[MAX_BUTTONS];
static char *button_command[MAX_BUTTONS];
pthread_t timer_thread;

static void show_main();

static void force_sync()
{
	system("sync;sync;sync");
}

static void quit_app()
{
	if (debug) printf("Exiting the app.\n");
	elm_exit();
	exit(0);

}

static void run_command(char *command)
{
	evas_object_hide(win);
	if (debug) printf("CMD: %s\n", command);
	char *cmd;
	asprintf(&cmd, "%s &", command);
	system(cmd);
	quit_app();
}

static void click_quit(void *data, Evas_Object * obj, void *event_info)
{
	quit_app();
}

// GENERIC FILE COPY
int file_copy(char *file_in, char *file_out)
{
	int fd_in;
	int fd_out;
	struct stat stat_data;
	off_t offset = 0;
	if (0 == access(file_in, R_OK)) {
		fd_in = open(file_in, O_RDONLY);
		fstat(fd_in, &stat_data);
		if ((fd_out =
		    open(file_out, O_WRONLY | O_CREAT, stat_data.st_mode))) {
			int result =
			    sendfile(fd_out, fd_in, &offset, stat_data.st_size);
			close(fd_in);
			close(fd_out);
			if (result) {
				if (debug) printf("Copy OK: %s -> %s\n", file_in,
					      file_out);
			} else {
				printf("Copy ERROR: %s -> %s\n", file_in,
				       file_out);
				return -1;
			}
		} else {
			printf("Error - Script '%s' not writable.\n", file_out);
			return -1;
		}
	} else {
		printf
		    ("Error - Script '%s' does not exist or is not readable.\n",
		     file_in);
		return -1;
	}
	return 0;
}


static Eina_Bool key_down_callback(void *data, int type, void *ev)
{
	Ecore_Event_Key *event = ev;
	if (0 == strcmp("Menu", event->key)
	    || 0 == strcmp("Super_L", event->key)
	    || 0 == strcmp("Super_R", event->key)) {
		quit_app();
	}
	if (debug) printf("Key: %s\n", event->key);
	return ECORE_CALLBACK_PASS_ON;
}

// GENERIC BUTTON CLICK HANDLER BEGIN
static void click_btn_generic(void *data, Evas_Object * obj, void *event_info)
{
	char *command;
	int btn_id = *((int *)data);
	const char *btn_name = button_name[btn_id];
	const char *btn_command = button_command[btn_id];
	if (debug) printf("Button clicked: %s [%d]\n", btn_name, btn_id);
	if (btn_command[0] == '@') {
		if (debug) printf("Opening new menu %s\n",btn_command);
		if (configuration_file != NULL) free(configuration_file);
		configuration_file=(char *)malloc(strlen(btn_command));
		memcpy(configuration_file,btn_command+1,strlen(btn_command));
		if (debug) printf("Opening new menu %s\n",configuration_file);
		show_main();
		return;
	} else if (btn_command[0] != '/')
		asprintf(&command, "%s/%s", scripts, btn_command);
	else
		asprintf(&command, "%s", btn_command);
	run_command(command);

}

// GENERIC BUTTON CLICK HANDLER END

// GENERIC CHECKBOX CLICK HANDLER BEGIN
static void click_checkbox_generic(void *data, Evas_Object * obj,
				   void *event_info)
{
	int btn_id = *((int *)data);
	if (debug) printf("Checkbox: %d -> %d\n", btn_id, chk_value[btn_id]);
	char *checkbox_script;
	asprintf(&checkbox_script, "%s/%s", scripts, button_command[btn_id]);
	char *checkbox_off_script;
	asprintf(&checkbox_off_script, "%s/off_%s", scripts,
		 button_command[btn_id]);
	char *auto_checkbox_script;
	asprintf(&auto_checkbox_script, "%s/auto/%s", scripts,
		 button_command[btn_id]);

	if (chk_value[btn_id] == 1) {
		if (0 == file_copy(checkbox_script, auto_checkbox_script)) {
			force_sync();
			run_command(checkbox_script);
		} else {
			chk_value[btn_id] = 0;
		}
	} else {
		if (0 == unlink(auto_checkbox_script)) {
			if (debug) printf("Delete OK: %s\n", auto_checkbox_script);
			if (0 == access(checkbox_off_script, X_OK))
				run_command(checkbox_off_script);
			quit_app();
		} else {
			chk_value[btn_id] = 1;
			printf("Delete ERROR: %s\n", auto_checkbox_script);
		}
	}
}

// GENERIC CHECKBOX CLICK HANDLER END
void fill_checkboxes()
{
	char *auto_script;
	int i;
	for (i = 0; i < MAX_BUTTONS; i++) {
		asprintf(&auto_script, "%s/auto/%s", scripts,
			 button_command[i]);
		if (0 == access(auto_script, X_OK)) {
			chk_value[i] = 1;
			if (debug) printf("Auto execute: %s\n", auto_script);
		}
	}
	free(auto_script);
}

static int configuration_load()
{
	FILE *fp;
	char *line = NULL;
	char *btn_name, *btn_command, *btn_type;
	size_t len = 0;
	ssize_t read;

	fp = fopen(configuration_file, "r");
	if (fp != NULL) {
		button_number=0;
		while ((read = getline(&line, &len, fp)) != -1
		       && button_number < MAX_BUTTONS) {
			line[strcspn(line, "\r\n")] = 0;
			if (line[0] == '#')
				continue;
			if (!strstr(line, "|"))
				continue;
			btn_type = strtok(line, "|");
			btn_name = strtok(NULL, "|");
			btn_command = strtok(NULL, "|");
			asprintf(&button_type[button_number], "%s", btn_type);
			asprintf(&button_name[button_number], "%s", btn_name);
			asprintf(&button_command[button_number], "%s",
				 btn_command);
			if (debug) printf("CONFIG:\t%s\t%s\n",
				      button_name[button_number],
				      button_command[button_number]);
			button_number++;
		}
		fclose(fp);
		free(line);
		free(btn_name);
		free(btn_command);
		free(btn_type);
		return 0;
	}
	printf("Invalid configuration file '%s'.\n", configuration_file);
	quit_app();
	return -1;
}

static int version_load()
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
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
	quit_app();
	return -1;
}

// Main GUI screen
void show_main()
{
	if (debug) printf("Running MOD_GUI\n");
	configuration_load();
	fill_checkboxes();
	elm_table_clear(table,EINA_TRUE);

	if (win == NULL) {
		win = elm_win_add(NULL, "NX-MOD GUI", ELM_WIN_DIALOG_BASIC);
		evas_object_smart_callback_add(win, "delete,request", click_quit, NULL);
		ecore_event_handler_add(ECORE_EVENT_KEY_DOWN, key_down_callback, NULL);
		box = elm_box_add(win);
		elm_win_resize_object_add(win, box);
		evas_object_show(box);
		table = elm_table_add(win);
		elm_box_pack_end(box, table);
	}


	// Start populating the table
	int first_button = 2;

	int btn_num = 0;
	if (button_number / 2 * button_height > SCREEN_HEIGHT)
		button_height = SCREEN_HEIGHT * 2 / button_number;
	for (btn_num = first_button; btn_num < first_button + button_number;
	     btn_num++) {
		datas[btn_num] = btn_num - first_button;
		if (0 ==
		    strcmp(button_type[btn_num - first_button], "checkbox")) {
			chk = elm_check_add(win);
			elm_object_style_set(chk, "transparent");
			evas_object_show(chk);
			evas_object_size_hint_min_set(chk, button_width,
						      button_height);
		}
		btn = elm_button_add(win);
		elm_object_style_set(btn, "transparent");
		elm_object_text_set(btn, (button_name[btn_num - first_button]));
		evas_object_show(btn);
		evas_object_size_hint_min_set(btn, button_width, button_height);
		bg2 = evas_object_rectangle_add(evas_object_evas_get(btn));
		evas_object_size_hint_min_set(bg2, button_width, button_height);
		evas_object_color_set(bg2, 20, 30, 40, 255);
		evas_object_show(bg2);
		bg = evas_object_rectangle_add(evas_object_evas_get(btn));
		evas_object_size_hint_min_set(bg, button_width - 2,
					      button_height - 2);
		evas_object_color_set(bg, 40, 60, 80, 255);
		evas_object_show(bg);
		elm_table_pack(table, bg2, btn_num % 2 + 1, btn_num / 2, 1, 1);
		elm_table_pack(table, bg, btn_num % 2 + 1, btn_num / 2, 1, 1);
		elm_table_pack(table, btn, btn_num % 2 + 1, btn_num / 2, 1, 1);
		if (0 ==
		    strcmp(button_type[btn_num - first_button], "checkbox"))
			elm_table_pack(table, chk, btn_num % 2 + 1, btn_num / 2,
				       1, 1);
		if (0 == strcmp(button_type[btn_num - first_button], "button"))
			evas_object_smart_callback_add(btn, "clicked",
						       click_btn_generic,
						       &datas[btn_num]);
		if (0 ==
		    strcmp(button_type[btn_num - first_button], "checkbox")) {
			elm_check_state_pointer_set(chk,
						    &(chk_value[btn_num - first_button]));
			evas_object_smart_callback_add(chk, "changed",
						       click_checkbox_generic,
						       &datas[btn_num]);
		}
	}

	evas_object_show(table);
	evas_object_show(win);
}

// Taken from https://stackoverflow.com/questions/1575278/function-to-split-a-filepath-into-path-and-file
void split_path_file(char **p, char **f, char *pf)
{
	char *slash = pf, *next;
	while ((next = strpbrk(slash + 1, "\\/")))
		slash = next;
	if (pf != slash)
		slash++;
	*p = strndup(pf, slash - pf);
	*f = strdup(slash);
}

// MAIN BEGIN

EAPI int elm_main(int argc, char **argv)
{
	if (argc <= 1) {
		exit(255);
	}
	if (argc > 1) {
		if (strcmp(argv[1], "help") == 0) {
			printf
			    ("Usage:\n%s [path_to_scripts_directory] [debug]\n\n\tpath_to_scripts_directory - default value: \"/mnt/mmc/scripts/\"\n\tdebug - if it is present debugging is on\n\n",
			     argv[0]);
			exit(0);
		}
	}
	version_load();
	if (strcmp(argv[argc - 1], "debug") == 0) {
		debug = 1;
	}
	if (strcmp(argv[argc - 1], "install") == 0) {
		debug = 1;
	} else {
		char *configuration_basename;
		split_path_file(&scripts, &configuration_basename, argv[1]);
		if (debug) printf("Scripts:%s\tConfiguration file:%s\n", scripts,
			      configuration_basename);
		if (strlen(configuration_basename) < 1) {
			asprintf(&configuration_file, "%s/%s%s", scripts,
				 "mod_gui.cfg.", version_model);
		} else {
			asprintf(&configuration_file, "%s.%s", argv[1],
				 version_model);
		}
		if (debug) printf("Configuration file: %s\n", configuration_file);
		if (debug) printf("Model: %s\nRelease: %s\n", version_model,
			      version_release);
		show_main();
	}

	if (debug) printf("Debug ON\n");

	elm_run();
	return 0;
}

ELM_MAIN()
// MAIN END
