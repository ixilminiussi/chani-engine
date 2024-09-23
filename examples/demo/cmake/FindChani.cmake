# FindChani.cmake - Find Chani libraries and headers

# FindChani
# This module find Chani libraries and headers for CMake.
# CHANI_HOME: The root directory where Chani is installed.

# set the default CHANI_HOME if not provided

if (NOT CHANI_HOME)
  set(CHANI_HOME "${CMAKE_CURRENT_LIST_DIR}/lib/chani" CACHE PATH "Chani installation directory")
endif()

# Find the Chani headers
find_path(CHANI_INCLUDE_DIR
  NAMES chani.h
  PATHS
    ${CHANI_HOME}/include
    /usr/local/include/chani
    /usr/include/chani
  )

find_library(CHANI_LIBRARY
  NAMES chani
  PATHS 
  ${CHANI_HOME}
  /usr/local
  PATH_SUFFIXES lib64 lib
)

# define the CHANI package
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Chani
  REQUIRED_VARS CHANI_INCLUDE_DIR CHANI_LIBRARY
  VERSION_VAR CHANI_VERSION
)

if (CHANI_FOUND)
  add_library(Chani UNKNOWN IMPORTED)
  set_target_properties(Chani PROPERTIES
    IMPORTED_LOCATION ${CHANI_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${CHANI_INCLUDE_DIR}
  )
else()
  message(FATAL_ERROR "Could not find Chani libraries.")
endif()
