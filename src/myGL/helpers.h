#ifndef HELPERS_H
#define HELPERS_H

#include "draw.h"

// draws each octant
static inline void draw_circle_pixels(Canvas* c, int xc, int yc, int x, int y, uint32_t colour) {
    put_pixel(c, xc + x, yc + y, colour);
    put_pixel(c, xc + y, yc + x, colour);
    put_pixel(c, xc - y, yc + x, colour);
    put_pixel(c, xc - x, yc + y, colour);
    put_pixel(c, xc - x, yc - y, colour);
    put_pixel(c, xc - y, yc - x, colour);
    put_pixel(c, xc + y, yc - x, colour);
    put_pixel(c, xc + x, yc - y, colour);
}

#endif