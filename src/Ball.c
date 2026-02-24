#include "Ball.h"

Ball ball_create(void) {
    return (Ball){.active    = true,
                  .id        = -1,
                  .x         = 0.0f,
                  .y         = 0.0f,
                  .radius    = 10.0f,
                  .vx        = 0.0f,
                  .vy        = 0.0f,
                  .speed     = 0.0f,
                  .prev_x    = 0.0f,
                  .prev_y    = 0.0f,
                  .colorRGBA = (ColorRGBA){.r = 255, .g = 0, .b = 0, .a = 255}};
}