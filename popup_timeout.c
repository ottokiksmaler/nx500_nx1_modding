/*
Compile with:

arm-linux-gnueabihf-gcc -o example example.c `pkg-config --cflags --libs elementary` --sysroot=/path_to_arm_usr_and_lib/ -Wl,-dynamic-linker,/lib/ld-2.13.so

We need to specify the correct ld or it will not work on device.
 */
#include <Elementary.h>
#include <sys/time.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>

pthread_t pt;
Evas_Object *win, *bg, *box, *lab;
char *message="No message given.",message_out[255];
int timeout=2;

static void
on_done(void *data, Evas_Object *obj, void *event_info)
{
   elm_exit();
   exit(0);
}

void* closePopup(void* arg) {
	sleep(timeout);
	elm_exit();
	exit(0);
}

EAPI int
elm_main(int argc, char **argv)
{
   if (argc > 1) {
	   message=argv[1];
   }
   if (argc > 2) {
	   timeout=atof(argv[2]);
   }
   strncpy(message_out,"<align=center>",20);
   strncat(message_out,message,200);
   strncat(message_out,"</align>",20);

   win = elm_win_add(NULL, "Info", ELM_WIN_DIALOG_BASIC);
   //evas_object_move(win, 1,1);
   elm_win_title_set(win, "Info");
   evas_object_smart_callback_add(win, "delete,request", on_done, NULL);


   /* add a standard bg */
   bg = elm_bg_add(win);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   box = elm_box_add(win);
   elm_win_resize_object_add(win, box);
   evas_object_show(box);

   lab = elm_label_add(win);
   elm_object_text_set(lab, message_out);
//    evas_object_size_hint_min_set(lab, 640, 120);
   elm_box_pack_end(box, lab);
   evas_object_show(lab);

   evas_object_show(win);
   
   pthread_create(&pt, NULL, &closePopup, NULL);
   
   elm_run();

   return 0;
}
ELM_MAIN()
