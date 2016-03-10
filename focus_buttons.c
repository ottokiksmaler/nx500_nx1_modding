/*
Compile with:

arm-linux-gnueabihf-gcc -o example example.c `pkg-config --cflags --libs elementary` --sysroot=/path_to_arm_usr_and_lib/ -Wl,-dynamic-linker,/lib/ld-2.13.so

We need to specify the correct ld or it will not work on device.
 */
#include <Elementary.h>
#include <strings.h>
#include <sys/time.h>
#define SCREEN_WIDTH 540
#define MAX_BUTTONS 40
#include <X11/Xlib.h>
#include <X11/keysym.h>

int debug = 0;
char *message =  "No message given", message_out[255], label_ok[255], label_cancel[255], label_entry[255], sample_text[255], label[255];
Evas_Object *win, *bg, *box, *button[MAX_BUTTONS];
unsigned int button_number,button_width, button_height, button_longpress, af_speed;
unsigned int af_positions[MAX_BUTTONS];
long long ts1, ts2;
char af_positions_file[255];

static void
restore_touch() {
	system("/usr/bin/st key touch click 360 240");
}

static void 
save_af_positions() 
{
	int i;
	FILE *f = fopen(af_positions_file, "w");
	for (i = 0; i < button_number; i++) {
		fprintf(f, "%d\n", af_positions[i]);
	}
	fclose(f);
}

static void 
load_af_positions() 
{
	FILE *fp;
    char * line = NULL;
    size_t len = 0, i=0;
    ssize_t read;

	fp  = fopen(af_positions_file, "r");
    if (fp != NULL) {
		while ((read = getline(&line, &len, fp)) != -1) {
			af_positions[i]=atoi(line);
			debug && printf("%d %d %s -> %d\n",(int)i,atoi(line),line,af_positions[i]);
			i++;
		}
		fclose(fp);
	}
//     fclose(fp);
// 	free(line);
}

static int
get_af_position()
{
	FILE *fp;
	char *spl=NULL;
	fp = popen("/usr/bin/st cap iq af pos","r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
	} else {
		if (fgets(message_out, sizeof(message_out)-1, fp) != NULL) {
			message_out[0]='_';
			spl=strtok(message_out," ");
			spl=strtok(NULL," ");
			spl=strtok(NULL," ");
		}
		pclose(fp);
		return atoi(spl);
	}
}

static void 
button_shortclick(const char * button_name) 
{
	int amount=0;
 	amount = af_positions[atoi(button_name)-1] - get_af_position();
	debug && printf("Focus to position: %s at %d by %d\n",button_name,af_positions[atoi(button_name)-1],amount);
	sprintf(message_out,"/usr/bin/st cap iq af mv 255 %d %d",amount,af_speed);
	debug && printf("CMD: %s\n",message_out);
	system(message_out);
 	restore_touch();
	
}

static void 
button_longclick(const char * button_name) 
{
	debug && printf("Save position: %s\n",button_name);
	int i = atoi(button_name)-1;
	af_positions[i] = get_af_position();
	debug && printf("Current position: %d\n",af_positions[i]);
	save_af_positions();
	restore_touch();
}

static void
quit_app(void *data, Evas_Object * obj, void *event_info)
{
	elm_exit ();
	exit (0);
}

long long
current_timestamp ()
{
  struct timeval te;
  gettimeofday (&te, NULL);
  long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
  return milliseconds;
}

static void
button_clicked (void *data, Evas_Object * obj, void *event_info)
{
  if (current_timestamp () - ts1 < button_longpress)
    {
		button_shortclick(elm_object_text_get(obj));
    }
}

static void
button_pressed (void *data, Evas_Object * obj, void *event_info)
{
  ts1 = current_timestamp ();
}

static void
button_unpressed (void *data, Evas_Object * obj, void *event_info)
{
  if (current_timestamp () - ts1 > button_longpress)
		button_longclick(elm_object_text_get(obj));
}

EAPI int
elm_main (int argc, char **argv)
{
  int i = 0;
  button_number=6;button_width=SCREEN_WIDTH/(button_number+1); button_height=45; button_longpress=500, af_speed=255;
  if (argc > 1) {
	  button_number=atoi(argv[1]);
	  if (button_number==0) {
		  printf("Usage:\npopup_focus [number of buttons [button height in px [longpress in ms [focus speed 1-255 [filename for focus positions]]]]]\n\n");
		  exit(0);
	  }
	  if (button_number>MAX_BUTTONS) button_number=MAX_BUTTONS;
	  button_width=SCREEN_WIDTH/(button_number+1);
  }
  if (argc > 2) {
	  button_height=atoi(argv[2]);
  }
  if (argc > 3) {
	  button_longpress=atoi(argv[3]);
  }
  if (argc > 4) {
	  af_speed=atoi(argv[4]);
  }
  
  if (argc > 5) {
	  strncpy(af_positions_file,argv[5],254);
  } else {
	  strncpy(af_positions_file,"/mnt/mmc/scripts/af_positions.txt",250);
  }
  
  win = elm_win_add (NULL, "Info", ELM_WIN_BASIC);
  evas_object_move (win, 60, 0);
  elm_win_title_set (win, "Info");
  evas_object_smart_callback_add (win, "delete,request", button_clicked,NULL);

  bg = elm_bg_add (win);
  elm_bg_color_set (bg, 0, 20, 30);
  elm_win_resize_object_add (win, bg);
  evas_object_show (bg);

  box = elm_box_add (win);
  elm_box_horizontal_set (box, EINA_TRUE);
  elm_win_resize_object_add (win, box);
  evas_object_show (box);

  for (i = 0; i < button_number; i++)
    {
      button[i] = elm_button_add (win);
	  af_positions[i]=1000;
// 	  printf("%s\n",elm_object_style_get(button[i]));
// 	  elm_object_style_set(button[i],"tizen");
      sprintf (label, "%d", i + 1);
      elm_object_text_set (button[i], label);
      evas_object_size_hint_min_set (button[i], button_width, button_height);
      elm_box_pack_end (box, button[i]);
      evas_object_show (button[i]);
      evas_object_smart_callback_add (button[i], "clicked", button_clicked,
				      NULL);
      evas_object_smart_callback_add (button[i], "pressed", button_pressed,
				      NULL);
      evas_object_smart_callback_add (button[i], "unpressed",
				      button_unpressed, NULL);
    }
  button[i] = elm_button_add (win);
  elm_object_text_set (button[i], "X");
  evas_object_size_hint_min_set (button[i], button_width, button_height);
  elm_box_pack_end (box, button[i]);
  evas_object_show (button[i]);
  evas_object_smart_callback_add (button[i], "clicked", quit_app, NULL);
  evas_object_show (win);
  restore_touch();
  load_af_positions();

//   evas_object_event_callback_add(win, 
// 			EVAS_CALLBACK_KEY_DOWN, key_down, NULL);

  elm_run ();
  return 0;
}

ELM_MAIN ()
