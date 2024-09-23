cmake_minimum_required(VERSION 3.12.0)
project(game VERSION 0.1.0 LANGUAGES C CXX)
include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(FMOD REQUIRED)
find_package(GLEW REQUIRED)
find_package(Chani REQUIRED)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB CHANI_SOURCE_FILES CONFIGURE_DEPENDS "../../src/*.cpp")

add_executable(game ${SOURCE_FILES}) 
include_directories(include ${SDL3_INCLUDE_DIRS})
target_link_libraries(game Chani FMOD::Core FMOD::Studio OpenGL::GL SDL3 SDL3_image GLEW::GLEW)
