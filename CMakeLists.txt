cmake_minimum_required(VERSION 3.12.0)
project(chani VERSION 0.1.0 LANGUAGES C CXX)
include(GNUInstallDirs)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(FMOD_HOME "${CMAKE_CURRENT_SOURCE_DIR}/lib/fmodstudioapi20223linux/fmod")

find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(GLEW REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(FMOD REQUIRED)

file(GLOB SOURCE_FILES  CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB INCLUDE_FILES CONFIGURE_DEPENDS "include/*.h")

add_library(chani SHARED ${SOURCE_FILES})
set_target_properties(chani PROPERTIES 
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR})

configure_file(chani.pc.in chani.pc @ONLY)

include_directories(PUBLIC include PRIVATE ${SDL3_INCLUDE_DIRS} ${FMOD_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})
target_link_libraries(chani FMOD::Core FMOD::Studio RapidJSON OpenGL::GL SDL3::SDL3 SDL3_image::SDL3_image GLEW::GLEW)

install(TARGETS chani
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/chani.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkconfig)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/chani)
