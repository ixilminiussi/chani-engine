cmake_minimum_required(VERSION 3.12.0)
project(simple-engine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GLEW REQUIRED)
find_package(RapidJSON REQUIRED)

add_executable(game 
    src/actor.cpp
    src/animSpriteComponent.cpp
    src/assets.cpp
    src/asteroid.cpp
    src/backgroundSpriteComponent.cpp
    src/circleCollisionComponent.cpp
    src/component.cpp
    src/game.cpp
    src/inputComponent.cpp
    src/log.cpp
    src/main.cpp
    src/moveComponent.cpp
    src/random.cpp
    src/rectangle.cpp
    src/renderer.cpp
    src/ship.cpp
    src/spriteComponent.cpp
    src/texture.cpp
    src/timer.cpp
    src/vector2.cpp
    src/window.cpp
    )

include_directories(include)

target_link_libraries(game RapidJSON OpenGL::GL SDL2::SDL2 SDL2_image GLEW::GLEW)
