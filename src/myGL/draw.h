#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>
#include "canvas.h"

// places pixel at (x, y)
static inline void put_pixel(Canvas* c, uint32_t x, uint32_t y, uint32_t color) {
    if (x < 0 || y < 0 || x > c->width || y > c->height) return;

    c->buffer[y * c->width + x] = color;
}

// (x1, y1) -> top left of rectangle, (x2, y2) -> bottom right of rectangle
static inline void draw_rect(Canvas* c, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color) {
    if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0 ||
        x1 > c->width || x2 > c->width || y1 > c->height || y2 > c->height) return;
    
    for (int i = y1; i < y2; i++) {
        for (int j = x1; j < x2; j++) {
            put_pixel(c, j, i, color);
        }
    }
}

#endif