#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

#define MAX_LEN_PATH (1024)

using namespace std;

/* Global array of images */
vector<string> name_images;


/* Create file names of images */
void scan_dir_for_images(const char *path) {
    string ext[] = {".bmp", ".jpg", ".png", ".jpeg", ".gif"};
    DIR *d;
    struct dirent *dir;

    /* get all file names from directory */
    d = opendir(path);
    if (d != NULL) {
	while ((dir = readdir(d)) != NULL) {
	    string fname = dir->d_name;

	    size_t found;
	    for (unsigned int i = 0; i < 5; ++i) {
		if ((found = fname.rfind(ext[i])) != string::npos) {
		    fname = path + string("/") + fname;
		    name_images.push_back(fname);
		    break;
		}
	    }
	}
	closedir(d);
    }
}


/* Create pixel buffer from file */
GdkPixbuf *create_pixbuf(const gchar * filename) {
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf) {
	cout << error->message << endl;
	g_error_free(error);
    }

    return pixbuf;
}



/* Handle for time alarm */
gboolean time_handler(GtkWidget *widget) {
    if (widget->window == NULL) return FALSE;

    time_t curtime;
    struct tm *loctime;
    char buffer[256] = {0,};

    curtime = time(NULL);
    loctime = localtime(&curtime);
    strftime(buffer, 256, "%T", loctime);
    cout << "Rise up at " << buffer << "\n";
    gtk_widget_queue_draw(widget);
    return TRUE;
}



/* MAIN */
int main(int argc, char **argv) {

    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *image;


    /* get alternative path for searching */
    string altPath;
    if (argc >= 2) {
	altPath = string(argv[1]);
    }

    /* get current working directory */
    char curWorkDir[MAX_LEN_PATH] = {0,};
    getcwd(curWorkDir, MAX_LEN_PATH);

    /* scan dirs for Images */
    scan_dir_for_images (curWorkDir);
    scan_dir_for_images (altPath.c_str());

    string path = "/home/dm/Downloads/girl.jpg";

    /* Init GTK */
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "IMAGE PROCESSING");
    gtk_container_set_border_width (GTK_CONTAINER(window), 5);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon.png"));

    image = gtk_image_new_from_file(path.c_str());
    gtk_container_add(GTK_CONTAINER(window), image);

    time_handler(window);
    gtk_widget_show_all(window);


    g_timeout_add(4000, (GSourceFunc) time_handler, (gpointer) window);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    time_handler(window);




    /* Main loop */
    gtk_main();

    return 0;
}