#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Block.h"
#include "Paddle.h"
#include "Infra.h"
#include <stdio.h>
#include <stdlib.h>

#define BACKGROUND_COLOR RAYWHITE
#define WINDOW_WIDTH 640 * 2
#define WINDOW_HEIGHT 360 * 2
#define FPS 120
#define FIXED_DELTATIME 1.0f / 120.0f
#define ROWS 8
#define COLS 15
#define MARGIN_BORDER 40.0f

typedef struct {
    Ball  *balls;
    Block *blocks;
    Paddle paddle;
    int    balls_count;
    int    blocks_count;
    bool   paused;
} Game;

Game game_create();

void game_init(void);
void game_update(float dt);
void game_render(void);
void game_destroy(void);

#endif