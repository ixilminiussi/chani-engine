cmake_minimum_required(VERSION 3.12.0)
project(simple-engine VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(RapidJSON REQUIRED)

add_executable(game 
    src/game.cpp
    src/log.cpp
    src/main.cpp
    src/renderer.cpp
    src/timer.cpp
    src/window.cpp
    )

include_directories(include)

target_link_libraries(game RapidJSON OpenGL::GL SDL2::SDL2 GLEW::GLEW)
