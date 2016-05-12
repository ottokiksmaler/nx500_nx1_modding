/*
Compile with:

arm-linux-gnueabi-gcc -Wall -o focus_stack focus_stack.c -s `pkg-config --cflags --libs ecore elementary` -lpthread --sysroot=../arm/ -Wl,-dynamic-linker,/lib/ld-2.13.so

We need to specify the correct ld or it will not work on device.
*/
#define _GNU_SOURCE
#include <Elementary.h>
#include <strings.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>

#define SCREEN_WIDTH 540
#define MAX_STEPS 100
#define DEFAULT_STEPS 10

static int debug = 1, running = 0;
static int alpha_value = 160;
static char *settings_file = "/root/focus_stack.cfg";
static char *caption_near = "Near";
static char *caption_far = "Far";
static char *caption_conf= "Conf.";
static char *caption_start = "Start";
static Evas_Object *lab, *win, *box, *btn_near, *btn_far, *btn_stack, *btn_quit, *entry_points, *entry_delay, *table, *btn_settings;
Evas_Object *popup_win;
Ecore_Timer *timer;
char stringline[255], label_entry[255], sample_text[255];
int focus_pos_near = 0, focus_pos_far = 0, focus_pos_min = 0, focus_pos_max =
    0, number_points = DEFAULT_STEPS, shot_delay = 6;
int button_height = 60, button_width = 120;

static void run_command(char *command)
{
	if (debug) printf("CMD: %s\n", command);
	system(command);
}

static void save_settings()
{
	FILE *f = fopen(settings_file, "w");
	if (f != NULL) {
		fprintf(f, "%d\n%d\n", number_points, shot_delay);
		fclose(f);
	}
}

static void load_settings()
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen(settings_file, "r");
	if (fp != NULL) {
		if (debug) printf("Reading configuration... ");
		if ((read = getline(&line, &len, fp)) != -1) {
			number_points = atoi(line);
		}
		if ((read = getline(&line, &len, fp)) != -1) {
			shot_delay = atoi(line);
		}
		fclose(fp);
		free(line);
		if (debug) printf ("%d %d\n",number_points, shot_delay);
	} else {
		printf ("Cannot access %s configuration file.\n",settings_file);
	}
}

static void click_quit(void *data, Evas_Object * obj, void *event_info)
{
	elm_exit();
	exit(0);
}

static Eina_Bool popup_hide()
{
	evas_object_hide(popup_win);
	return ECORE_CALLBACK_CANCEL;
}

static void popup_show(char *message, int timeout, int row)
{
	if (popup_win) {
		evas_object_hide(popup_win);
	} 
	popup_win = elm_win_add(NULL, "Info", ELM_WIN_BASIC);
	elm_win_prop_focus_skip_set(popup_win, EINA_TRUE);


	Evas_Object *popup_box;
	popup_box = elm_box_add(popup_win);
	elm_win_resize_object_add(popup_win, popup_box);
	evas_object_size_hint_min_set(popup_box, SCREEN_WIDTH, button_height);
	evas_object_show(popup_box);
	
	Evas_Object *table;
	table = elm_table_add(popup_win);
	elm_box_pack_end(popup_box, table);
	evas_object_show(table);

	lab = elm_label_add(popup_win);
	evas_object_size_hint_min_set(lab, SCREEN_WIDTH, button_height);
	elm_object_text_set(lab, message);
	evas_object_show(lab);
	Evas_Object *bg;
	bg = evas_object_rectangle_add(evas_object_evas_get(lab));
	evas_object_size_hint_min_set(bg, SCREEN_WIDTH, button_height);
	evas_object_color_set(bg, 0, 0, 0, 128);
	evas_object_show(bg);
	elm_table_pack(table, bg, 1, 1, 1, 1);
	elm_table_pack(table, lab, 1, 1, 1, 1);

	evas_object_move(popup_win, 60, button_height * row);
	evas_object_show(popup_win);

	if (timeout > 0)
		ecore_timer_add(timeout, popup_hide, NULL);
}

static int get_af_position()
{
	FILE *fp;
	char *spl = NULL;
	fp = popen("/usr/bin/st cap iq af pos", "r");
	if (fp == NULL) {
		if (debug) printf("Failed get current focus position\n");
		return 0;
	} else {
		if (fgets(stringline, sizeof(stringline) - 1, fp) != NULL) {
			stringline[0] = '_';	// fix st output
			spl = strtok(stringline, " ");
			spl = strtok(NULL, " ");
			spl = strtok(NULL, " ");
		}
		pclose(fp);
		if (debug) printf("Current focus position: %s\n", spl);
		return atoi(spl);
	}
}

static void focus_to_position(int position)
{
	int amount = 0;
	amount = position - get_af_position();
	sprintf(stringline, "/usr/bin/st cap iq af mv 255 %d 255", amount);
	run_command(stringline);
}

static void focus_move(int amount)
{
	sprintf(stringline, "/usr/bin/st cap iq af mv 255 %d 255", amount);
	run_command(stringline);
}

static void run_stack(int near, int far, int steps, int delay)
{
	int current_position = 0, step = 0;
	double delta = 0;
	char *stack_message="";
	if (near == 0) {
		popup_show("<align=center>Please set Near.</align>", 2, 1);
		return;
	}
	if (far == 0) {
		popup_show("<align=center>Please set Far.</align>", 2, 1);
		return;
	}
	
	if (debug)  printf("Stacking - Near: %d \tFar: %d \tPhotos: %d \tDelay: %d\n",
		   near, far, steps, delay);
	run_command("/usr/bin/st app nx capture af-mode manual\n");	// show manual focus mode
	run_command("/usr/bin/st cap capdtm setusr AFMODE 0x70003\n");	// force manual focus mode
	sleep(1);
	focus_to_position(near);
	sleep(2);
	current_position = get_af_position();
	delta = ((double)(far - current_position)) / (double)(steps - 1);
	if (debug) printf("far: %d current: %d delta: %f\n", far, current_position, delta);
// 	while (current_position >= far && step < steps && step < MAX_STEPS) {
	while (step < steps && step < MAX_STEPS) {
		step++;
		asprintf(&stack_message, "#%d of %d",step,steps);
		popup_show(stack_message,1,0);

		sleep(delay / 2);
//		run_command("/usr/bin/st app nx capture single && /bin/sleep 0.5 && /usr/bin/st key click s1\n");	// capture single frame and exit photo preview is exists
        run_command("st key push s1 && sleep 0.3 && st key click s2 && st key release s1 && sleep 0.5 && st key click s1\n"); // capture single frame and exit photo preview is exists
		if (step == steps)
			break;
		sleep(delay - delay / 2);
		focus_move((int)
			   (near + (int)(step * delta) - current_position));
		current_position = near + (int)(step * delta);
	}
}

static void click_near(void *data, Evas_Object * obj, void *event_info)
{
	popup_show("<align=center>Near focus position set.</align>", 2, 1);
	focus_pos_near = get_af_position();
}

static void click_far(void *data, Evas_Object * obj, void *event_info)
{
	popup_show("<align=center>Far focus position set.</align>", 2, 1);
	focus_pos_far = get_af_position();
}

void * thread_stack(void *arg) {
	char *message;
	evas_object_hide(win);
	asprintf (&message, "<align=center>Making %d photos with delay %ds</align>",number_points,shot_delay);
	popup_show(message,0,0);
	running = 1;
	run_stack(focus_pos_near, focus_pos_far, number_points, shot_delay);
 	evas_object_hide(popup_win);
	evas_object_show(win);
	return (void *)0;
}

static void click_stack(void *data, Evas_Object * obj, void *event_info)
{
	pthread_t timer_thread;
	pthread_create(&timer_thread, NULL, &thread_stack, NULL);
}

static void settings_ok()
{
	evas_object_hide(popup_win);
	int i = atoi(elm_object_text_get(entry_points));
	if (i > 0)
		number_points = i;
	i = atoi(elm_object_text_get(entry_delay));
	if (i > 0)
		shot_delay = i;
	char message[255];
	sprintf(message, "<align=center>Frames: %d  delay: %ds</align>",
		number_points, shot_delay);
	popup_show(message, 2, 3);
	if (debug) printf("Frames: %d\n", i);
	save_settings();
}

static void entry_show(int row)
{
	popup_win = elm_win_add(NULL, "Entry", ELM_WIN_BASIC);
	evas_object_move(popup_win, 60, button_height * row);
	Evas_Object *bg;
	bg = elm_bg_add(popup_win);
	elm_win_resize_object_add(popup_win, bg);
	evas_object_show(bg);

	Evas_Object *popup_box;
	popup_box = elm_box_add(popup_win);
	elm_box_horizontal_set(popup_box, EINA_TRUE);
	elm_win_resize_object_add(popup_win, popup_box);
	evas_object_show(popup_box);

	Evas_Object *lab;
	lab = elm_label_add(popup_win);
	elm_object_text_set(lab, "Frames:");
	evas_object_size_hint_min_set(lab, 140, button_height);
	elm_box_pack_end(popup_box, lab);
	evas_object_show(lab);

	char steps_string[255];
	sprintf(steps_string, "%d", number_points);
	entry_points = elm_entry_add(popup_win);
	elm_entry_input_panel_layout_set(entry_points,ELM_INPUT_PANEL_LAYOUT_NUMBERONLY);
	elm_object_text_set(entry_points, steps_string);
	evas_object_show(entry_points);
	evas_object_size_hint_min_set(entry_points, 100, button_height);
	evas_object_show(entry_points);
	elm_box_pack_end(popup_box, entry_points);

	Evas_Object *lab_2;
	lab_2 = elm_label_add(popup_win);
	elm_object_text_set(lab_2, "Delay:");
	evas_object_size_hint_min_set(lab_2, 140, button_height);
	elm_box_pack_end(popup_box, lab_2);
	evas_object_show(lab_2);

	sprintf(steps_string, "%d", shot_delay);
	entry_delay = elm_entry_add(popup_win);
	elm_entry_input_panel_layout_set(entry_delay,ELM_INPUT_PANEL_LAYOUT_NUMBERONLY);
	elm_object_text_set(entry_delay, steps_string);
	evas_object_show(entry_delay);
	evas_object_size_hint_min_set(entry_delay, 100, button_height);
	evas_object_show(entry_delay);
	elm_box_pack_end(popup_box, entry_delay);

	Evas_Object *ok;
	ok = elm_button_add(popup_win);
	elm_object_text_set(ok, "OK");
	evas_object_size_hint_min_set(ok, 100, button_height);
	elm_box_pack_end(popup_box, ok);
	evas_object_show(ok);

	evas_object_show(popup_win);
	elm_object_focus_set(entry_points, EINA_TRUE);

	evas_object_smart_callback_add(ok, "clicked", settings_ok, NULL);
}

static void click_settings(void *data, Evas_Object * obj, void *event_info)
{
	entry_show(1);
}

static void video_sweep() {
	int near, far;
	char *command;
	run_command("/usr/bin/st cap lens focus far");
	sleep(1);
	far = get_af_position();
	run_command("/usr/bin/st cap lens focus near");
	sleep(1);
	near = get_af_position();
	sleep(1);
	run_command("st key click del; sleep 1; st key click fn; sleep 1; st key click rec; sleep 0.5");
	asprintf(&command,"/usr/bin/st cap iq af mv 255 %d 2", (int)(far-near));
	run_command(command);
	run_command("st key click rec");
}

EAPI int elm_main(int argc, char **argv)
{
	load_settings();
	if (argc > 1) {
		if (!strcmp(argv[1], "help")) {
			printf
			    ("Usage:\nfocus_stack [ help | sweep | number_of_photos [ delay_between_photos [ button_height [ button_width ] ] ] ]\n\n");
			exit(0);
		}
		if (0==strcmp(argv[1], "sweep")) {
			video_sweep();
			exit(0);
		} else {
			number_points = atoi(argv[1]);
		}
		if (argc > 2) {
			shot_delay = atoi(argv[2]);
		}
		if (argc > 3) {
			button_height = atoi(argv[3]);
		}
		if (argc > 4) {
			button_width = atoi(argv[4]);
		}
	}

	printf("Stacking with %d photos at %d delay and %d button height\n",
	       number_points, shot_delay, button_height);

	win = elm_win_add(NULL, "Focus stacker", ELM_WIN_BASIC);
	elm_win_prop_focus_skip_set(win, EINA_TRUE);
	evas_object_move(win, 55, 0);
	evas_object_smart_callback_add(win, "delete,request", click_quit, NULL);

	box = elm_box_add(win);
	elm_box_horizontal_set(box, EINA_TRUE);
	elm_win_resize_object_add(win, box);
	evas_object_show(box);
	table = elm_table_add(win);
	elm_box_pack_end(box, table);

	Evas_Object *bg;
	evas_object_size_hint_min_set(box, SCREEN_WIDTH, button_height);

	btn_near = elm_button_add(win);
	elm_object_style_set(btn_near, "transparent");
	elm_object_text_set(btn_near, caption_near);
	evas_object_show(btn_near);
	evas_object_size_hint_min_set(btn_near, button_width, button_height);
	bg = evas_object_rectangle_add(evas_object_evas_get(btn_near));
	evas_object_size_hint_min_set(bg, button_width, button_height);
	evas_object_color_set(bg, 40, 60, 80, alpha_value);
	evas_object_show(bg);
	elm_table_pack(table, bg, 1, 1, 1, 1);
	elm_table_pack(table, btn_near, 1, 1, 1, 1);

	evas_object_smart_callback_add(btn_near, "clicked", click_near, NULL);

	btn_far = elm_button_add(win);
	elm_object_style_set(btn_far, "transparent");
	elm_object_text_set(btn_far, caption_far);
	evas_object_show(btn_far);
	evas_object_size_hint_min_set(btn_far, button_width, button_height);
	bg = evas_object_rectangle_add(evas_object_evas_get(btn_far));
	evas_object_size_hint_min_set(bg, button_width, button_height);
	evas_object_color_set(bg, 20, 40, 60, alpha_value);
	evas_object_show(bg);
	elm_table_pack(table, bg, 2, 1, 1, 1);
	elm_table_pack(table, btn_far, 2, 1, 1, 1);

	evas_object_smart_callback_add(btn_far, "clicked", click_far, NULL);

	btn_settings = elm_button_add(win);
	elm_object_style_set(btn_settings, "transparent");
	elm_object_text_set(btn_settings, caption_conf);
	evas_object_show(btn_settings);
	evas_object_size_hint_min_set(btn_settings, 80, button_height);
	bg = evas_object_rectangle_add(evas_object_evas_get(btn_settings));
	evas_object_size_hint_min_set(bg, 120, button_height);
	evas_object_color_set(bg, 40, 80, 40, alpha_value);
	evas_object_show(bg);
	elm_table_pack(table, bg, 6, 1, 1, 1);
	elm_table_pack(table, btn_settings, 6, 1, 1, 1);

	evas_object_smart_callback_add(btn_settings, "clicked", click_settings,
				       NULL);

	btn_stack = elm_button_add(win);
	elm_object_style_set(btn_stack, "transparent");
	elm_object_text_set(btn_stack, caption_start);
	evas_object_show(btn_stack);
	evas_object_size_hint_min_set(btn_stack, button_width, button_height);
	bg = evas_object_rectangle_add(evas_object_evas_get(btn_stack));
	evas_object_size_hint_min_set(bg, button_width, button_height);
	evas_object_color_set(bg, 40, 60, 80, alpha_value);
	evas_object_show(bg);
	elm_table_pack(table, bg, 7, 1, 1, 1);
	elm_table_pack(table, btn_stack, 7, 1, 1, 1);

	evas_object_smart_callback_add(btn_stack, "clicked", click_stack, NULL);

	btn_quit = elm_button_add(win);
	elm_object_style_set(btn_quit, "transparent");
	elm_object_text_set(btn_quit, " X ");
	evas_object_show(btn_quit);
	evas_object_size_hint_min_set(btn_quit, 80, button_height);
	bg = evas_object_rectangle_add(evas_object_evas_get(btn_quit));
	evas_object_size_hint_min_set(bg, 80, button_height);
	evas_object_color_set(bg, 80, 40, 20, alpha_value);
	evas_object_show(bg);
	elm_table_pack(table, bg, 8, 1, 1, 1);
	elm_table_pack(table, btn_quit, 8, 1, 1, 1);

	evas_object_smart_callback_add(btn_quit, "clicked", click_quit, NULL);

	evas_object_show(table);
	evas_object_show(win);

	elm_run();
	return 0;
}

ELM_MAIN()
