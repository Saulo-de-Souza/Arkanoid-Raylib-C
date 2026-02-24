#include "Block.h"

Block block_create(void) {
    return (Block){
        .active         = true,
        .id             = -1,
        .x              = 0.0f,
        .y              = 0.0f,
        .w              = 100.0f,
        .h              = 25.0f,
        .vx             = 0.0f,
        .vy             = 0.0f,
        .speed          = 0.0f,
        .prev_x         = 0.0f,
        .prev_y         = 0.0f,
        .colorRGBA      = (ColorRGBA){0, 0, 255, 255},
        .count_breaking = 0,
    };
}