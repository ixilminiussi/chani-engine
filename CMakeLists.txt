cmake_minimum_required(VERSION 3.12.0)
project(chani VERSION 0.1.0 LANGUAGES C CXX)
include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(FMOD REQUIRED)

# Source and Include Files
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB INCLUDE_FILES CONFIGURE_DEPENDS "include/*.h")

# ImGui Setup
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)
file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp)
file(GLOB IMGUI_BACKEND_SOURCES 
  ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
  ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
)

# Add Library
add_library(chani SHARED ${SOURCE_FILES} ${IMGUI_SOURCES} ${IMGUI_BACKEND_SOURCES})
set_target_properties(chani PROPERTIES 
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Includes
target_include_directories(chani 
  PUBLIC include 
  PRIVATE ${SDL3_INCLUDE_DIRS} ${FMOD_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS} ${IMGUI_DIR} ${IMGUI_DIR}/backends
)

# Linking
target_link_libraries(chani FMOD::Core FMOD::Studio OpenGL::GL SDL3 SDL3_image)

# Installation
configure_file(chani.pc.in chani.pc @ONLY)

install(TARGETS chani
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/chani.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/chani)

