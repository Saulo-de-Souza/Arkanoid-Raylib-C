#ifndef INFRA_H
#define INFRA_H

#include "Ball.h"
#include "Block.h"
#include "Paddle.h"
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------
// BLOCK
//------------------------------------------
void infra_render_block(Block *block);
void infra_update_block(Block *block, float dt);
void infra_destroy_block(Block *block);

//------------------------------------------
// BALL
//------------------------------------------
void infra_render_ball(Ball *ball);
void infra_update_ball(Ball *ball, float dt, int window_width, int window_height, float margin_border);
void infra_destroy_ball(Ball *ball);

//------------------------------------------
// PADDLE
//------------------------------------------
void infra_render_paddle(const Paddle paddle);
void infra_update_paddle(Paddle *paddle, float dt, int window_width, int window_height, float margin_border);
void infra_destroy_paddle(Paddle *paddle);

//------------------------------------------
// HELPERS
//------------------------------------------
static Color infra_to_rgba(ColorRGBA colorRGBA);

void infra_init(void);
void infra_destroy(void);
void infra_render(void);

typedef enum SoundName { BALL_SOUND = 0, BLOCK_SOUND, ARENA_SOUND } SoundName;
void infra_play_sound(SoundName name);

void infra_check_collision(Ball *ball, Block *block);
void infra_check_collision_paddle(Ball *ball, Paddle paddle);

void infra_set_balls_lost_count(int value);
void infra_set_blocks_lost_count(int value);
int  infra_get_balls_lost_count();
int  infra_get_blocks_lost_count();

Texture2D load_texture_checked(const char *path);
Sound     load_sound_checked(const char *path);
#endif