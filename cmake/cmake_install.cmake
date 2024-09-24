# Install script for directory: /home/ixilminiussi/Desktop/gamedev/chani-engine

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libchani.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libchani.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/cmake/libchani.so.0.1.0"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/cmake/libchani.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libchani.so.0.1.0"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib64/libchani.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/usr/local/lib/fmod/core/x86_64:/usr/local/lib/fmod/studio/x86_64:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE SHARED_LIBRARY FILES "/home/ixilminiussi/Desktop/gamedev/chani-engine/cmake/libchani.so")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkconfig" TYPE FILE FILES "/home/ixilminiussi/Desktop/gamedev/chani-engine/cmake/chani.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/chani" TYPE FILE FILES
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/FPSCameraComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/actor.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/animSpriteComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/assets.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/audioComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/audioSystem.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/backgroundSpriteComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/cameraComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/chani.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/circleCollisionComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/component.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/cube.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/directionalLight.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/followCameraComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/gamepadState.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/iRenderer.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/inputComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/inputSystem.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/keyboardState.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/log.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/material.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/maths.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/matrix4.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/mesh.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/meshComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/mouseState.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/moveComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/orbitCameraComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/phongMaterial.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/plane.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/quaternion.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/random.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/rectangle.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/rendererOGL.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/shader.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/soundEvent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/sphere.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/spline.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/splineActor.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/splineCameraComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/spriteComponent.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/spriteMaterial.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/texture.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/timer.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/vector2.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/vector3.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/vertexArray.h"
    "/home/ixilminiussi/Desktop/gamedev/chani-engine/include/window.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ixilminiussi/Desktop/gamedev/chani-engine/cmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
