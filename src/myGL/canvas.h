#ifndef CANVAS_H
#define CANVAS_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    Display* display;
    Window window;
    XImage* ximage;
    uint32_t* buffer;
    int width;
    int height;
    GC gc;
} Canvas;

// initialise the window and allocate pixel buffer
static inline Canvas* create_canvas(int width, int height) {
    Canvas* c = malloc(sizeof(Canvas));
    c->width = width;
    c->height = height;

    c->display = XOpenDisplay(NULL);
    int screen = DefaultScreen(c->display);

    c->window = XCreateSimpleWindow(
        c->display, RootWindow(c->display, screen),
        100, 100, width, height, 0, 0, 0
    );

    // pixel memory
    c->buffer = (uint32_t*)calloc((size_t)(width * height), sizeof(uint32_t));

    c->ximage = XCreateImage(
        c->display, DefaultVisual(c->display, screen), DefaultDepth(c->display, screen),
        ZPixmap, 0, (char*)c->buffer, (unsigned int)width, (unsigned int)height, 32, 0
    );

    XSelectInput(c->display, c->window, ExposureMask | KeyPressMask);
    XMapWindow(c->display, c->window);
    c->gc = DefaultGC(c->display, screen);

    return c;
}

static inline void update_canvas(Canvas* c) {
    XPutImage(c->display, c->window, c->gc, c->ximage, 0, 0, 0, 0, c->width, c->height);
    XFlush(c->display);
}

static inline void fill_canvas(Canvas* c, uint32_t colour) {
    for (size_t i = 0; i < c->width * c->height; i++) {
        c->buffer[i] = colour;
    }
}

static inline void close_canvas(Canvas* c) {
    XDestroyImage(c->ximage);
    XDestroyWindow(c->display, c->window);
    XCloseDisplay(c->display);
    free(c);
}

#endif