/*
Compile with:

arm-linux-gnueabi-gcc -o onscreen_key onscreen_key.c `pkg-config --cflags --libs ecore elementary` -lecore_input --sysroot=../arm/ -Wl,-dynamic-linker,/lib/ld-2.13.so

We need to specify the correct ld or it will not work on device.

Usage:

onscreen_key [Label] [button] [x y] [width height]

Displays a button at given coordinates (default 400 0) of given size (default 120 60) with given label (default REC) and clicks given button (default rec)
To dismiss long-click it for at least five seconds.

Record - rec, OK - ok, Half-shutter - S1, Full-shutter - S2, Menu - menu, etc.

*/
#include <Elementary.h>
#include <strings.h>
#include <unistd.h>
#include <Ecore.h>
#include <Ecore_Input.h>
#include <sys/time.h>
#include <pthread.h>

Evas_Object *win, *bg, *box, *button_key, *button_quit;
char *key_osd="REC", *key_click="rec", *label, *command;
int debug=1;
static struct timeval previous_time_loop, current_time_loop, time_press, time_release;
pthread_t timer_thread, cleanup_thread;

static void quit_app()
{
   elm_exit();
   exit(0);
}

long msec_passed(struct timeval *fromtime, struct timeval *totime)
{
  long msec;
  msec=(totime->tv_sec-fromtime->tv_sec)*1000;
  msec+=(totime->tv_usec-fromtime->tv_usec)/1000;
  return msec;
}

// Detect sleep events
void* timer_loop(void* arg) {
	int timer_sleep=1;
	long msec_elapsed;
	while(1) {
		gettimeofday(&previous_time_loop, NULL); 
		sleep(timer_sleep);
		gettimeofday(&current_time_loop, NULL); 
		msec_elapsed = msec_passed(&previous_time_loop,&current_time_loop);
		if (msec_elapsed>(timer_sleep*1000+300)) quit_app();
	}
}


static void button_click(void *data, Evas_Object *obj, void *event_info)
{
	printf("Running: %s\n",(char *)data);
	system((char *) data);
}

static void button_press(void *data, Evas_Object *obj, void *event_info)
{
	if (strcmp("pressed",(char *)data) == 0) 
		gettimeofday(&time_press, NULL);
	if (strcmp("unpressed",(char *)data) == 0) {
		gettimeofday(&time_release, NULL);
		if (msec_passed(&time_press, &time_release)>5000)
			quit_app();
	}
	
	
}

EAPI int
elm_main(int argc, char **argv)
{
	// detect power-off and quit on it
	pthread_create(&cleanup_thread, NULL, &timer_loop, NULL);
	int x=400, y=0, w=120, h=60;
   if (argc > 1) {
	   key_osd=argv[1];
   }
   if (argc > 2) {
	   key_click=argv[2];
   }
   if (argc > 4) {
	   x=atoi(argv[3]);
	   y=atoi(argv[4]);
   }
   if (argc > 6) {
	   w=atoi(argv[5]);
	   h=atoi(argv[6]);
   }
   asprintf(&label,"%s",key_osd);
   asprintf(&command,"st key click %s",key_click);

	win = elm_win_add(NULL, "Info", ELM_WIN_NOTIFICATION);
	elm_win_prop_focus_skip_set(win, EINA_TRUE);
	evas_object_move(win, x, y);

	Evas_Object *popup_box;
	popup_box = elm_box_add(win);
	elm_win_resize_object_add(win, popup_box);
	evas_object_size_hint_min_set(popup_box, w, h);
	evas_object_show(popup_box);
	
	Evas_Object *table;
	table = elm_table_add(win);
	elm_box_pack_end(popup_box, table);
	evas_object_show(table);

	button_key = elm_button_add(win);
	elm_object_style_set(button_key, "transparent");
	elm_object_text_set(button_key, label);
	evas_object_size_hint_min_set(button_key, w, h);
	evas_object_show(button_key);
	Evas_Object *bg;
	bg = evas_object_rectangle_add(evas_object_evas_get(button_key));
	evas_object_size_hint_min_set(bg, w, h);
	evas_object_color_set(bg, 40, 80, 100, 255);
	evas_object_show(bg);
	elm_table_pack(table, bg, 1, 1, 1, 1);

	bg = evas_object_rectangle_add(evas_object_evas_get(button_key));
	evas_object_size_hint_min_set(bg, w-2, h-2);
	evas_object_color_set(bg, 0, 0, 0, 255);
	evas_object_show(bg);
	elm_table_pack(table, bg, 1, 1, 1, 1);

	elm_table_pack(table, button_key, 1, 1, 1, 1);
	evas_object_show(win);
	evas_object_smart_callback_add(button_key, "clicked",button_click,command);
	evas_object_smart_callback_add(button_key, "pressed",button_press,"pressed");
	evas_object_smart_callback_add(button_key, "unpressed",button_press,"unpressed");

   elm_run();

   return 0;
}
ELM_MAIN()
