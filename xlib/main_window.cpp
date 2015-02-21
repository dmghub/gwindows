/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

int main() {

    Display *ourDisplay;
    ourDisplay = XOpenDisplay(NULL);

    if (ourDisplay == NULL) {
	printf("Не удалось установить соединение с графическим терминалом.\n");
        return 1;
    };

    int ourScreen = DefaultScreen(ourDisplay);          // Экран по-умолчанию
    Window rootWindow = RootWindow(ourDisplay, ourScreen); // Корневое окно
    long bgcolor = WhitePixel(ourDisplay, ourScreen);    // Белый цвет экрана

    Window myWindow = XCreateSimpleWindow(ourDisplay,rootWindow,100, 100, 320, 200, 0, 0, bgcolor);
    XMapWindow(ourDisplay, myWindow);
    XFlush(ourDisplay);

    sleep(5);

    XDestroyWindow(ourDisplay, myWindow);
    XCloseDisplay(ourDisplay);

    return 0;
};

*/

#include <iostream>
#include <string>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

using namespace std;

extern int errno;

int main(int argc, char **argv) {
    Display *d;
    Window w;
    XEvent e;

    string msg = "Hello, World!";
    int s;

    d = XOpenDisplay(getenv("DISPLAY"));
    if (NULL == d) {
	cout << "Can't connect X server: " << strerror(errno) << "\n";
	exit (1);
    }

    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1, BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    while (1) {
	XNextEvent(d, &e);
	if (Expose == e.type) {
	    XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10 ); 
	    XDrawString(d, w, DefaultGC(d, s), 50, 50, msg.c_str(), msg.length()); 
	}
	
	if (KeyPress == e.type) {
	    break;
	}
    }
//    sleep(5);
    XDestroyWindow(d, w);
    XCloseDisplay(d);
    return 0;
}
