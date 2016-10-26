/*
Compile with:

arm-linux-gnueabihf-gcc -o button_png button_png.c `pkg-config --cflags --libs ecore elementary` -lecore_input --sysroot=../arm/ -Wl,-dynamic-linker,/lib/ld-2.13.so


how to use: 
./button_png filename command x y w h

ex:
button_png /opt/usr/nx-ks/ks.png "echo test"  200 80 100 60

*/

#include <Elementary.h>
#include <sys/resource.h>
Evas_Object *win, *img;
char *file, *command;

void _on_keydown (void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	system(command);
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{

	setpriority(PRIO_PROCESS, 0, +15);

	int x, y, w, h;


	if (argc > 1) {
	   file=argv[1];
	}
	if (argc > 2) {
	   command=argv[2];
	}
	if (argc > 3) {
	   x=atof(argv[3]);
	}
	if (argc > 4) {
	   y=atof(argv[4]);
	}
	if (argc > 5) {
	   w=atof(argv[5]);
	}
	if (argc > 6) {
	   h=atof(argv[6]);
	} else {
	   printf("how to use: ./button_png filename command x y w h \n");
	   elm_exit();
	   exit(0);
	}


	win = elm_win_add(NULL, NULL, ELM_WIN_NOTIFICATION);
	elm_win_prop_focus_skip_set(win, EINA_TRUE);

	Evas *evas = evas_object_evas_get(win);
	evas_object_move(win, x, y); evas_object_resize(win,w,h);
	evas_object_show(win);

	// Create an image object
	Evas_Object *img = evas_object_image_filled_add(evas);
	evas_object_image_file_set(img, file, NULL);
	evas_object_move(img, 0, 0); evas_object_resize(img,w,h);
	evas_object_event_callback_add(img, EVAS_CALLBACK_MOUSE_DOWN, _on_keydown, NULL);
	evas_object_show(img);

	ecore_main_loop_iterate();
   
   elm_run();

   return 0;
}
ELM_MAIN()
