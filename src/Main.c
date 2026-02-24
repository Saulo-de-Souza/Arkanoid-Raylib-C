
#include "Infra.h"
#include "Ball.h"
#include "Game.h"
#include <stdio.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

float accumulator_deltatime = 0.0f;

void update_frame() {
    float dt = GetFrameTime();
    if (dt > 0.1f) {
        dt = 0.1f;
    }
    accumulator_deltatime += dt;
    int safety = 0;
    while (accumulator_deltatime >= FIXED_DELTATIME) {
        game_update(FIXED_DELTATIME);
        accumulator_deltatime -= FIXED_DELTATIME;
        if (++safety > 5) {
            break;
        }
    }

    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);

    game_render();

    EndDrawing();
}

int main(int argc, char *argv[]) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Arkanoid");
    InitAudioDevice();
    SetTargetFPS(FPS);
    SetExitKey(0);
    Image icon = LoadImage("assets/icon-16.png");
    SetWindowIcon(icon);

    game_init();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(update_frame, 0, 1);
#else
    while (!WindowShouldClose()) {
        update_frame();
    }
#endif
    UnloadImage(icon);
    game_destroy();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}