#include "Paddle.h"

Paddle paddle_create(void) {
    return (Paddle){.active     = true,
                    .x          = 0.0f,
                    .y          = 0.0f,
                    .w          = 100.0f,
                    .h          = 25.0f,
                    .speed      = 0.0f,
                    .vx         = 0.0f,
                    .vy         = 0.0f,
                    .prev_x     = 0.0f,
                    .prev_y     = 0.0f,
                    .anim_frame = 0,
                    .anim_timer = 0.0f,
                    .colorRGBA  = (ColorRGBA){.r = 0, .g = 255, .b = 0, .a = 255}};
}