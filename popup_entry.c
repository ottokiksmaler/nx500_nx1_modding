/*
Compile with:

arm-linux-gnueabihf-gcc -o example example.c `pkg-config --cflags --libs elementary` -lecore_input --sysroot=/path_to_arm_usr_and_lib/ -Wl,-dynamic-linker,/lib/ld-2.13.so

We need to specify the correct ld or it will not work on device.
 */
#include <Elementary.h>
#include <strings.h>
#include <Ecore.h>
#include <Ecore_Input.h>

char *message="No message given",message_out[255], label_ok[255], label_cancel[255], label_entry[255], sample_text[255];
Evas_Object *win, *bg, *bg2, *bgl, *box, *box2, *lab, *button_ok, *button_cancel, *entry_field, *entry_frame;
int debug=0;

static void
ok_button_1_clicked(void *data, Evas_Object *obj, void *event_info)
{
   printf("%s",elm_object_text_get(entry_field));
   elm_exit();
   exit(0);
}

static void
ok_button_2_clicked(void *data, Evas_Object *obj, void *event_info)
{
   /* quit the mainloop (elm_run) */
   elm_exit();
   exit(255);
}

static Eina_Bool key_down_callback(void *data, int type, void *ev)
{
   Ecore_Event_Key *event = ev;
   if (!strcmp("KP_Enter", event->key))
   {
	   ok_button_1_clicked(NULL, NULL, NULL);
   }
   if (!strcmp("Menu", event->key))
   {
	   ok_button_2_clicked(NULL, NULL, NULL);
   }
   debug && printf("Key: %s\n",event->key);
   return ECORE_CALLBACK_PASS_ON;
}

EAPI int
elm_main(int argc, char **argv)
{
   if (argc > 1) {
	   message=argv[1];
   }
   strncpy(label_ok,"OK",10);
   strncpy(label_cancel,"CANCEL",10);
   strncpy(sample_text,"",100);
   if (argc > 2) {
	   strncpy(label_ok,argv[2],255);
   }
   if (argc > 3) {
	   strncpy(label_cancel,argv[3],255);
   }
   if (argc > 4) {
	   strncpy(sample_text,argv[4],255);
   }
   strncpy(message_out,"<align=center>",20);
   strncat(message_out,message,210);
   strncat(message_out,"</align>",20);

   win = elm_win_add(NULL, "Info", ELM_WIN_BASIC);
   evas_object_move(win, 0,0);
   elm_win_title_set(win, "Info");
   evas_object_smart_callback_add(win, "delete,request", ok_button_1_clicked, NULL);

   bg = elm_bg_add(win);
   elm_bg_color_set(bg, 0,20,30);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   box = elm_box_add(win);
   elm_win_resize_object_add(win, box);
   evas_object_size_hint_padding_set(box, 2, 2, 2, 2);
   evas_object_show(box);

   lab = elm_label_add(win);
   elm_label_line_wrap_set(lab,ELM_WRAP_WORD);
   elm_object_text_set(lab, message_out);
   evas_object_size_hint_min_set(lab, 720, 60);
   elm_box_pack_end(box, lab);
   evas_object_show(lab);

   Evas_Object* etable = elm_table_add(win);
   entry_field = elm_entry_add(win);
   elm_entry_single_line_set(entry_field, EINA_TRUE);
   elm_object_text_set(entry_field, sample_text);
   evas_object_resize(entry_field,720,60);
   evas_object_color_set(entry_field, 100, 200, 255,255);
   elm_box_pack_end(box, etable);
   
   bg2 = elm_bg_add(win);
   elm_bg_color_set(bg2, 255,0,0);
   evas_object_resize(bg2,640,60);
   evas_object_show(bg2);
   evas_object_show(entry_field);

   elm_table_pack(etable,bg2,1,1,1,1);
   elm_table_pack(etable,entry_field,1,1,1,1);
   evas_object_show(etable);
   
   box2 = elm_box_add(win);
   elm_box_horizontal_set(box2, EINA_TRUE);
   elm_box_pack_end(box, box2);
   evas_object_show(box2);

   button_ok = elm_button_add(win);
   elm_object_text_set(button_ok, label_ok);
   evas_object_size_hint_min_set(button_ok, 360, 60);
   elm_box_pack_end(box2, button_ok);
   evas_object_show(button_ok);
   evas_object_smart_callback_add(button_ok, "clicked", ok_button_1_clicked, NULL);

   button_cancel = elm_button_add(win);
   elm_object_text_set(button_cancel, label_cancel);
   evas_object_size_hint_min_set(button_cancel, 360, 60);
   elm_box_pack_end(box2, button_cancel);
   evas_object_show(button_cancel);
   evas_object_smart_callback_add(button_cancel, "clicked", ok_button_2_clicked, NULL);

   elm_object_focus_set(entry_field, EINA_TRUE);
   evas_object_show(win);
   ecore_event_handler_add(ECORE_EVENT_KEY_DOWN, key_down_callback, NULL);

   elm_run();

   return 0;
}
ELM_MAIN()
