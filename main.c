/*
  * 창 안에 상자를 그려내는 단순 Xlib 응용 프로그램입니다.
  * gcc input.c -o output -lX11
  */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Display *display;
    Window window;
    XEvent event;
    char *msg = "Hello, World!";
    int s;

    /* 서버 연결 개시 */
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "display를 열 수 없습니다\n");
        exit(1);
    }

    s = DefaultScreen(display);

    /* 창 만들기 */
    window = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 200, 200, 1,
                           BlackPixel(display, s), WhitePixel(display, s));

    /* 이용하려는 이벤트 종류 선택 */
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    /* 창 보이기 */
    XMapWindow(display, window);

    /* 이벤트 루프 */
    while (1) {
        XNextEvent(display, &event);

        /* 창을 (다시) 그리기 */
        if (event.type == Expose) {
            XFillRectangle(display, window, DefaultGC(display, s), 20, 20, 10, 10);
            XDrawString(display, window, DefaultGC(display, s), 50, 50, msg, strlen(msg));
        }
        /* 키 눌림이 있으면 끝내기 */
        if (event.type == KeyPress)
            break;
    }

    /* 서버 연결 닫기 */
    XCloseDisplay(display);

    return 0;
 }