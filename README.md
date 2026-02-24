# Arkanoid Clone (C + raylib)

A clean and modular **Arkanoid-style game** written in pure C using
raylib.

This project was created as an educational example demonstrating:

- Fixed timestep game loop
- Manual memory management (malloc / realloc / free)
- Modular architecture (Game / Infra / Entities)
- Collision detection (circle vs AABB)
- Asset loading with validation
- Native desktop build and Web (Emscripten) support

---

## Project Structure

    ARKANOID/
    │
    ├── assets/              # Textures, sounds, icon
    ├── include/             # Public headers
    │   ├── Ball.h
    │   ├── Block.h
    │   ├── Game.h
    │   ├── Infra.h
    │   ├── Paddle.h
    │   └── Types.h
    │
    ├── src/                 # Source files
    │   ├── Ball.c
    │   ├── Block.c
    │   ├── Game.c
    │   ├── Infra.c
    │   ├── Main.c
    │   └── Paddle.c
    │
    ├── lib/
    │   ├── raylib/
    │   └── emsdk/
    │
    ├── CMakeLists.txt
    ├── Makefile
    └── build.bat

---

## Architecture Overview

The project follows a lightweight engine-style separation:

- **Game** → High-level game state and rules
- **Infra** → Rendering, audio, collisions and low-level systems
- **Entities** → Ball, Block, Paddle (data-oriented structs)

Game loop uses:

- Fixed timestep simulation
- Accumulator pattern
- Frame-time clamping to avoid spiral of death

---

## Controls

- Move paddle: Mouse
- Pause / Resume: Right Mouse Button or ESC
- Close: Disabled (custom exit handling)

---

## Requirements

- C compiler (GCC or Clang recommended)
- raylib
- CMake (optional)
- Make (optional)
- Emscripten (for Web build)

---

## Build (Desktop)

### Using Makefile

    make

## Build (WebAssembly)

    build.bat web

The project exports to buil/web and runs in the browser.

---

## Assets Handling

Assets are validated at load time:

- Textures checked via `texture.id`
- Sounds checked via `sound.stream.buffer`

Fatal errors abort execution to prevent undefined behavior.

---

## Features

- Multi-ball spawning
- Block damage states
- Paddle animation
- Sound effects
- Win condition detection
- Clean resource cleanup

---

## Educational Goals

This project demonstrates:

- Memory ownership in C
- Safe realloc usage
- Separation of concerns
- Collision resolution with penetration correction
- Reflection vector math
- Deterministic simulation step
