#include "Infra.h"

Sound     ball_sound;
Sound     block_sound;
Sound     arena_sound;
Texture2D ball_texture;
Texture2D block_texture;
Texture2D block_breaking_texture;
Texture2D paddle_texture;
Texture2D paddle_texture_1;
Texture2D paddle_texture_2;
Texture2D paddle_texture_3;
Texture2D background;

int balls_lost_count;
int blocks_lost_count;

void infra_init() {
    ball_sound  = load_sound_checked("assets/audios/bfh1_wood_hit_01.ogg");
    block_sound = load_sound_checked("assets/audios/bfh1_falling_06.ogg");
    arena_sound = load_sound_checked("assets/audios/bfh1_wood_hit_02.ogg");

    ball_texture           = load_texture_checked("assets/textures/ball.png");
    block_texture          = load_texture_checked("assets/textures/block_yellow.png");
    block_breaking_texture = load_texture_checked("assets/textures/block_yellow_breaking.png");
    paddle_texture_1       = load_texture_checked("assets/textures/paddle_1.png");
    paddle_texture_2       = load_texture_checked("assets/textures/paddle_2.png");
    paddle_texture_3       = load_texture_checked("assets/textures/paddle_3.png");
    background             = load_texture_checked("assets/textures/background.png");

    balls_lost_count  = 0;
    blocks_lost_count = 0;
}

void infra_destroy() {

    if (ball_sound.stream.buffer) {
        UnloadSound(ball_sound);
    }
    if (block_sound.stream.buffer) {
        UnloadSound(block_sound);
    }
    if (arena_sound.stream.buffer) {
        UnloadSound(arena_sound);
    }
    if (ball_texture.id > 0) {
        UnloadTexture(ball_texture);
    }
    if (block_texture.id > 0) {
        UnloadTexture(block_texture);
    }
    if (block_breaking_texture.id > 0) {
        UnloadTexture(block_breaking_texture);
    }
    if (paddle_texture_1.id > 0) {
        UnloadTexture(paddle_texture_1);
    }
    if (paddle_texture_2.id > 0) {
        UnloadTexture(paddle_texture_2);
    }
    if (paddle_texture_3.id > 0) {
        UnloadTexture(paddle_texture_3);
    }
    if (paddle_texture.id > 0) {
        UnloadTexture(paddle_texture);
    }
    if (background.id > 0) {
        UnloadTexture(background);
    }
}

void infra_render(void) {
    DrawTexturePro(background, (Rectangle){0, 0, 762, 957}, (Rectangle){0, 0, 1280, 720}, (Vector2){0, 0}, 0.0f, RAYWHITE);
}

void infra_set_balls_lost_count(int value) {
    balls_lost_count = value;
}
void infra_set_blocks_lost_count(int value) {
    blocks_lost_count = value;
}
int infra_get_balls_lost_count() {
    return balls_lost_count;
}
int infra_get_blocks_lost_count() {
    return blocks_lost_count;
}

//-----------------------------------------
// BLOCK
//-----------------------------------------
void infra_render_block(Block *block) {
    if (block == NULL) {
        return;
    }
    if (block->active) {
        Rectangle texture_src  = {0.0f, 0.0f, 384.0f, 128.0f};
        Rectangle texture_dest = {block->x, block->y, block->w, block->h};
        Vector2   origin       = {0.0f, 0.0f};
        DrawTexturePro(block->count_breaking == 0 ? block_texture : block_breaking_texture, texture_src, texture_dest, origin, 0.0f, RAYWHITE);
    }
}

void infra_update_block(Block *block, float dt) {
    if (block == NULL) {
        return;
    }
    if (block->active) {
        block->prev_x = block->x;
        block->prev_y = block->y;

        block->x += block->vx * dt * block->speed;
        block->y += block->vy * dt * block->speed;
    }
}

void infra_destroy_block(Block *block) {
    if (block == NULL) {
        return;
    }
}

//-----------------------------------------
// BALL
//-----------------------------------------
void infra_render_ball(Ball *ball) {
    if (ball == NULL) {
        return;
    }
    if (ball->active) {
        float     diameter     = ball->radius * 2.0f;
        Rectangle texture_src  = {0.0f, 0.0f, 128.0f, 128.0f};
        Rectangle texture_dest = {ball->x, ball->y, diameter, diameter};
        Vector2   origin       = {diameter / 2.0f, diameter / 2.0f};
        DrawTexturePro(ball_texture, texture_src, texture_dest, origin, 0.0f, RAYWHITE);
    }
}

void infra_update_ball(Ball *ball, float dt, int window_width, int window_height, float margin_border) {
    if (ball == NULL) {
        return;
    }
    if (ball->active) {
        ball->prev_x = ball->x;
        ball->prev_y = ball->y;

        ball->x += ball->vx * dt * ball->speed;
        ball->y += ball->vy * dt * ball->speed;

        if (ball->x - ball->radius < 0.0f + margin_border || ball->x + ball->radius > window_width - margin_border) {
            ball->vx *= -1.0f;
            infra_play_sound(ARENA_SOUND);
        }
        if (ball->y - ball->radius < 0.0f + margin_border / 2) {
            ball->vy *= -1.0f;
            infra_play_sound(ARENA_SOUND);
        }

        if (fabs(ball->vy) < 0.5f) {
            ball->vy = (ball->vy < 0 ? -0.5f : 0.5f);
        }

        if (ball->y >= window_height && ball->active) {
            ball->active = false;
            balls_lost_count += 1;
        }
    }
}

void infra_destroy_ball(Ball *ball) {
    if (ball == NULL) {
        return;
    }
}

//------------------------------------------
// PADDLE
//------------------------------------------
void infra_render_paddle(const Paddle paddle) {
    if (paddle.anim_frame == 0) {
        paddle_texture = paddle_texture_1;
    } else if (paddle.anim_frame == 1) {
        paddle_texture = paddle_texture_2;
    } else {
        paddle_texture = paddle_texture_3;
    }

    Rectangle texture_src  = {0.0f, 0.0f, 485.0f, 128.0f};
    Rectangle texture_dest = {paddle.x, paddle.y, paddle.w, paddle.h};
    Vector2   origin       = {0.0f, 0.0f};
    DrawTexturePro(paddle_texture, texture_src, texture_dest, origin, 0.0f, RAYWHITE);
}

void infra_update_paddle(Paddle *paddle, float dt, int window_width, int window_height, float margin_border) {
    if (paddle == NULL) {
        return;
    }
    if (paddle->active) {
        paddle->vx = 0.0f;
        paddle->vy = 0.0f;

        paddle->prev_x = paddle->x;
        paddle->prev_y = paddle->y;

        paddle->x = GetMousePosition().x - paddle->w / 2;

        if (paddle->x < 0.0f + margin_border) {
            paddle->x = 0.0f + margin_border;
        } else if (paddle->x + paddle->w > window_width - margin_border) {
            paddle->x = window_width - paddle->w - margin_border;
        }
        paddle->vx = (paddle->x - paddle->prev_x) / dt;
        paddle->vy = (paddle->y - paddle->prev_y) / dt;

        paddle->anim_timer += dt;
        if (paddle->anim_timer >= 0.1f) {
            paddle->anim_timer = 0.0f;
            paddle->anim_frame++;

            if (paddle->anim_frame > 2) {
                paddle->anim_frame = 0;
            }
        }
    }
}

void infra_destroy_paddle(Paddle *paddle) {
    if (paddle == NULL) {
        return;
    }
}

//-----------------------------------------
// METHODS
//-----------------------------------------
static Color infra_to_rgba(ColorRGBA colorRGBA) {
    return (Color){colorRGBA.r, colorRGBA.g, colorRGBA.b, colorRGBA.a};
}

void infra_play_sound(SoundName name) {
    switch (name) {
    case BALL_SOUND: {
        PlaySound(ball_sound);
        break;
    }
    case BLOCK_SOUND: {
        PlaySound(block_sound);
        break;
    }
    case ARENA_SOUND: {
        PlaySound(arena_sound);
        break;
    }
    default: {
        break;
    }
    }
}

void infra_check_collision(Ball *ball, Block *block) {
    if (ball == NULL || block == NULL) {
        return;
    }
    if (!block->active || !ball->active) {
        return;
    }

    Rectangle rect = {block->x, block->y, block->w, block->h};

    float closestX = fmaxf(rect.x, fminf(ball->x, rect.x + rect.width));
    float closestY = fmaxf(rect.y, fminf(ball->y, rect.y + rect.height));

    float dx = ball->x - closestX;
    float dy = ball->y - closestY;

    float distanceSq = dx * dx + dy * dy;

    if (distanceSq > ball->radius * ball->radius) {
        return;
    }

    float distance = sqrtf(distanceSq);
    if (distance == 0.0f) {
        return;
    }

    infra_play_sound(BLOCK_SOUND);

    block->count_breaking += 1;
    if (block->count_breaking >= 2) {
        block->active = false;
        blocks_lost_count += 1;
    }

    float nx = dx / distance;
    float ny = dy / distance;

    float penetration = ball->radius - distance;
    ball->x += nx * penetration;
    ball->y += ny * penetration;

    float dot = ball->vx * nx + ball->vy * ny;

    ball->vx -= 2.0f * dot * nx;
    ball->vy -= 2.0f * dot * ny;
}

void infra_check_collision_paddle(Ball *ball, Paddle paddle) {
    if (ball == NULL) {
        return;
    }
    if (!paddle.active || !ball->active) {
        return;
    }

    Rectangle rect = {paddle.x, paddle.y, paddle.w, paddle.h};

    float closestX = fmaxf(rect.x, fminf(ball->x, rect.x + rect.width));
    float closestY = fmaxf(rect.y, fminf(ball->y, rect.y + rect.height));

    float dx = ball->x - closestX;
    float dy = ball->y - closestY;

    float distanceSq = dx * dx + dy * dy;

    if (distanceSq > ball->radius * ball->radius) {
        return;
    }

    float distance = sqrtf(distanceSq);
    if (distance == 0.0f) {
        return;
    }

    infra_play_sound(BALL_SOUND);

    float nx = dx / distance;
    float ny = dy / distance;

    float penetration = ball->radius - distance;
    ball->x += nx * penetration;
    ball->y += ny * penetration;

    float dot = ball->vx * nx + ball->vy * ny;

    ball->vx -= 2.0f * dot * nx;
    ball->vy -= 2.0f * dot * ny;
}

Texture2D load_texture_checked(const char *path) {
    Texture2D tex = LoadTexture(path);

    if (tex.id == 0) {
        TraceLog(LOG_FATAL, "Erro ao carregar textura: %s", path);
        exit(EXIT_FAILURE);
    }

    return tex;
}

Sound load_sound_checked(const char *path) {
    Sound snd = LoadSound(path);

    if (snd.stream.buffer == NULL) {
        TraceLog(LOG_FATAL, "Erro ao carregar som: %s", path);
        exit(EXIT_FAILURE);
    }

    return snd;
}