cmake_minimum_required(VERSION 3.10)
project(Arkanoid)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
file(GLOB_RECURSE SOURCES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib/include
)

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    raylib 
    opengl32 
    gdi32 
    winmm
)

# target_link_options(${PROJECT_NAME} PRIVATE -mconsole) use -mconsole to dev
target_link_options(${PROJECT_NAME} PRIVATE -mwindows)

if(WIN32)
    enable_language(RC)
    set(CMAKE_RC_COMPILER_INIT windres)
    target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/icon.rc)
endif()


