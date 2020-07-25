#include <X11/Xlib.h>
#include <assert.h>
#include <unistd.h>

#define NIL (0)

main()
{
    Display *dpy = XOpenDisplay(NIL);
    assert(dpy);
    Window w = XCreateWindow(dpy, DefaultRootWindow(dpy), 0, 0,
                            200, 100, 0,
                            CopyFromParent, CopyFromParent, CopyFromParent,
                            NIL, 0);
    XMapWindow(dpy, w);
    XFlush(dpy);
    sleep(10);
}