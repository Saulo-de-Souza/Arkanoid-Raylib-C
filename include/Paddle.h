#ifndef PADDLE_H
#define PADDLE_H

#include "Types.h"
#include "stdbool.h"

typedef struct {
    bool      active;
    float     x;
    float     y;
    float     w;
    float     h;
    float     speed;
    float     vx;
    float     vy;
    float     prev_x;
    float     prev_y;
    ColorRGBA colorRGBA;
    int       anim_frame;
    float     anim_timer;
} Paddle;

Paddle paddle_create(void);

#endif