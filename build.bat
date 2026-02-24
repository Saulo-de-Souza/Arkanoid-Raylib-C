@echo off

if %1 == web (
    call lib\emsdk\emsdk_env.bat
    emmake make wasm
) else (
    if %1 == win (
        make
    ) else (
        if %1 == serve (
            php -S localhost:8000 -t build/web
        )
    )
)


