cmake_minimum_required(VERSION 3.12.0)
project(simple-engine VERSION 0.1.0 LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FMOD_HOME "${CMAKE_CURRENT_SOURCE_DIR}/lib/fmodstudioapi20223linux/fmod")

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(GLEW REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(FMOD REQUIRED)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(game ${SOURCE_FILES})

include_directories(include ${SDL3_INCLUDE_DIRS} ${FMOD_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})

target_link_libraries(game FMOD::Core FMOD::Studio RapidJSON OpenGL::GL SDL3::SDL3 SDL3_image::SDL3_image GLEW::GLEW)
