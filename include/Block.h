#ifndef BLOCK_H
#define BLOCK_H

#include "Types.h"
#include <stdbool.h>

typedef struct {
    bool      active;
    int       id;
    float     x;
    float     y;
    float     w;
    float     h;
    float     vx;
    float     vy;
    float     speed;
    float     prev_x;
    float     prev_y;
    ColorRGBA colorRGBA;
    int       count_breaking;
} Block;

Block block_create(void);

#endif