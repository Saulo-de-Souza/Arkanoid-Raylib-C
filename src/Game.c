#include "Game.h"

Game game;

Game game_create() {
    Game game;

    game.balls_count  = 1;
    game.blocks_count = ROWS * COLS;

    game.balls  = malloc(sizeof(Ball) * game.balls_count);
    game.blocks = malloc(sizeof(Block) * game.blocks_count);

    /* =========================
       BALLS
       ========================= */
    Ball ball      = ball_create();
    ball.x         = WINDOW_WIDTH / 2.0f;
    ball.y         = WINDOW_HEIGHT - 30.0f - 2.0f * ball.radius;
    ball.speed     = 500.0f;
    ball.vx        = 1.0f;
    ball.vy        = -1.0f;
    ball.colorRGBA = (ColorRGBA){.r = 255, .g = 255, .b = 255, .a = 255};

    game.balls[0] = ball;

    /* =========================
       BLOCK GRID
       ========================= */
    float margin_x = 120.0f;
    float start_y  = 90.0f;
    float spacing  = 5.0f;

    float total_width = WINDOW_WIDTH - (margin_x * 2.0f) - (spacing * (COLS - 1));
    float block_w     = total_width / COLS;
    float block_h     = 40.0f;

    int index = 0;

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            Block block = block_create();

            block.w = block_w;
            block.h = block_h;

            block.x = margin_x + col * (block_w + spacing);
            block.y = start_y + row * (block_h + spacing);

            block.colorRGBA = (ColorRGBA){.r = 255, .g = 255, .b = 0, .a = 255};

            game.blocks[index] = block;
            index++;
        }
    }

    /* =========================
       PADDLE
       ========================= */
    Paddle paddle    = paddle_create();
    paddle.x         = WINDOW_WIDTH / 2.0f - paddle.w / 2.0f;
    paddle.y         = WINDOW_HEIGHT - paddle.h - 20.0f;
    paddle.colorRGBA = (ColorRGBA){.r = 255, .g = 255, .b = 255, .a = 255};

    game.paddle = paddle;

    game.paused = true;

    return game;
}

void game_init() {
#ifndef PLATFORM_WEB
    DisableCursor();
#endif
    game = game_create();
    infra_init();
}

void game_update(float dt) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsKeyPressed(KEY_ESCAPE)) {
        game.paused = !game.paused;

        if (game.paused) {
#ifndef PLATFORM_WEB
            EnableCursor();
#endif
            game.paddle.active = false;
        } else {
            if (game.blocks_count == infra_get_blocks_lost_count()) {
                infra_set_blocks_lost_count(0);
            }
#ifndef PLATFORM_WEB
            DisableCursor();
#endif
            game.paddle.active = true;
            SetMousePosition(game.paddle.x + game.paddle.w / 2, game.paddle.y + game.paddle.h / 2);
        }
    }

    if (game.paused) {
        return;
    }

    if (game.balls_count == infra_get_balls_lost_count()) {
        game.paused        = true;
        game.paddle.x      = WINDOW_WIDTH / 2.0f - game.paddle.w / 2.0f;
        game.paddle.y      = WINDOW_HEIGHT - game.paddle.h - 20.0f;
        game.paddle.active = false;

        Ball *temp = realloc(game.balls, sizeof(Ball));
        if (temp != NULL) {
            game.balls[0].x      = WINDOW_WIDTH / 2.0f;
            game.balls[0].y      = WINDOW_HEIGHT - 60.0f - 2.0f * game.balls[0].radius;
            game.balls[0].vy     = -1.0f;
            game.balls[0].active = true;
            game.balls_count     = 1;
        } else {
            TraceLog(LOG_ERROR, "Falha ao alocar memória para nova bola");
        }

        infra_set_balls_lost_count(0);
    }

    if ((infra_get_blocks_lost_count() == 3 || infra_get_blocks_lost_count() == 13 || infra_get_blocks_lost_count() == 100) &&
        game.balls_count == 1) {
        int new_count = game.balls_count + 1;

        Ball *temp = realloc(game.balls, sizeof(Ball) * new_count);

        Ball ball      = ball_create();
        ball.x         = WINDOW_WIDTH / 2.0f;
        ball.y         = WINDOW_HEIGHT - 30.0f - 2.0f * ball.radius;
        ball.speed     = 500.0f;
        ball.vx        = 1.0f;
        ball.vy        = -1.0f;
        ball.colorRGBA = (ColorRGBA){.r = 255, .g = 255, .b = 255, .a = 255};

        if (temp != NULL) {
            game.balls                = temp;
            game.balls[new_count - 1] = ball;
            game.balls_count          = new_count;
        }
    }

    infra_update_paddle(&game.paddle, dt, WINDOW_WIDTH, WINDOW_HEIGHT, MARGIN_BORDER);

    for (int x = 0; x < game.balls_count; ++x) {
        infra_update_ball(&game.balls[x], dt, WINDOW_WIDTH, WINDOW_HEIGHT, MARGIN_BORDER);
    }

    for (int x = 0; x < game.blocks_count; ++x) {
        infra_update_block(&game.blocks[x], dt);
    }

    for (int x = 0; x < game.balls_count; ++x) {
        infra_check_collision_paddle(&game.balls[x], game.paddle);
        for (int i = 0; i < game.blocks_count; ++i) {
            infra_check_collision(&game.balls[x], &game.blocks[i]);
        }
    }
}

void game_render() {
    infra_render();

    infra_render_paddle(game.paddle);

    for (int x = 0; x < game.balls_count; ++x) {
        infra_render_ball(&game.balls[x]);
    }

    for (int x = 0; x < game.blocks_count; ++x) {
        infra_render_block(&game.blocks[x]);
    }

    if (game.blocks_count == infra_get_blocks_lost_count()) {
        game.paused = true;
        DrawText("You won!", 400, 450, 40, WHITE);

        for (int x = 0; x < game.blocks_count; ++x) {
            game.blocks[x].active         = true;
            game.blocks[x].count_breaking = 0;

            game.paddle.x        = WINDOW_WIDTH / 2.0f - game.paddle.w / 2.0f;
            game.paddle.y        = WINDOW_HEIGHT - game.paddle.h - 20.0f;
            game.paddle.active   = false;
            game.balls[0].x      = WINDOW_WIDTH / 2.0f;
            game.balls[0].y      = WINDOW_HEIGHT - 60.0f - 2.0f * game.balls[0].radius;
            game.balls[0].vy     = -1.0f;
            game.balls[0].active = true;
            infra_set_balls_lost_count(0);
        }
    }

    if (game.paused) {
        DrawText("Click the right mouse button", 400, 500, 40, WHITE);
    }

    char text_blocks[64];
    snprintf(text_blocks, sizeof(text_blocks), "Blocks: %d", infra_get_blocks_lost_count());
    DrawText(text_blocks, 50, 25, 20, WHITE);
}

void game_destroy() {
    for (int x = 0; x < game.balls_count; ++x) {
        infra_destroy_ball(&game.balls[x]);
    }

    for (int x = 0; x < game.blocks_count; ++x) {
        infra_destroy_block(&game.blocks[x]);
    }

    free(game.balls);
    free(game.blocks);
    infra_destroy();
}
