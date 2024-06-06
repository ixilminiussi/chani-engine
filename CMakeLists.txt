cmake_minimum_required(VERSION 3.12.0)
project(simple-engine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(GLEW REQUIRED)
find_package(RapidJSON REQUIRED)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(game ${SOURCE_FILES})

include_directories(include)

target_link_libraries(game RapidJSON OpenGL::GL SDL2::SDL2 SDL2_image GLEW::GLEW)
