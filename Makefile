.PHONY: all build setup clean run git assets

EXE = build/Arkanoid.exe
m = "add"

all:	run
	

build:	setup
	cmake --build build

setup:	assets
	cmake -S . -B build -G "MinGW Makefiles"

clean:
	cmake -E rm -rf "build"

run:	build
	$(EXE)

git:
	git add --all
	git commit -m "$(m)"
	git push origin master

assets:
	cmake -E copy_directory assets build/assets

wasm:
	mkdir -p build/web
	emcc src/Main.c src/Game.c src/Infra.c src/Ball.c src/Block.c src/Paddle.c \
    -o build/web/index.html \
    -I./lib/raylib/webassembly/include \
	-I./include \
    -L./lib/raylib/webassembly/lib \
    -lraylib \
    -s USE_GLFW=3 \
    -s ASYNCIFY \
    -s FORCE_FILESYSTEM=1 \
	-DPLATFORM_WEB \
	--preload-file assets
