#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>
#include "canvas.h"

static inline void put_pixel(Canvas* c, int x, int y, uint32_t color);

#include "helpers.h"

// places pixel at (x, y)
static inline void put_pixel(Canvas* c, int x, int y, uint32_t color) {
    if (x < 0 || y < 0 || x > c->width || y > c->height) return;

    c->buffer[y * c->width + x] = color;
}

// (x1, y1) -> top left of rectangle, (x2, y2) -> bottom right of rectangle
static inline void draw_rect(Canvas* c, int x1, int y1, int x2, int y2, uint32_t color) {
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 ||
        x1 > c->width || x2 > c->width || y1 > c->height || y2 > c->height) return;
    
    for (int i = y1; i < y2; i++) {
        for (int j = x1; j < x2; j++) {
            put_pixel(c, j, i, color);
        }
    }
}

// uses bresenhams line algorithm to draw line between p1 and p2 for any slope
static inline void draw_line(Canvas* c, int x1, int y1, int x2, int y2, uint32_t colour) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int x = x1;
    int y = y1;

    // check if the line is m > 1
    if (dx >= dy) {
        int err = (dy << 1) - dx;

        for (int i = 0; i <= dx; i++) {
            put_pixel(c, x, y, colour);

            if (err >= 0) {
                y += sy;
                err -= (dx << 1);
            }
            x += sx;
            err += (dy << 1);
        }
    } else {
        int err = (dx << 1) - dy;
        
        for (int i = 0; i <= dy; i++) {
            put_pixel(c, x, y, colour);

            if (err >= 0) {
                x += sx;
                err -= (dy << 1);
            }
            y += sy;
            err += (dx << 1);
        }
    }
}

static inline void draw_circle(Canvas* c, int xc, int yc, int r, uint32_t colour) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    draw_circle_pixels(c, xc, yc, x, y, colour);

    while (y >= x) {
        x++;

        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }

        draw_circle_pixels(c, xc, yc, x, y, colour);
    }
}

#endif