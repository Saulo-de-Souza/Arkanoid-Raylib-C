#ifndef BALL_H
#define BALL_H

#include "Types.h"
#include "stdbool.h"

typedef struct {
    bool      active;
    int       id;
    float     x;
    float     y;
    float     radius;
    float     vx;
    float     vy;
    float     speed;
    float     prev_x;
    float     prev_y;
    ColorRGBA colorRGBA;
} Ball;

Ball ball_create(void);

#endif