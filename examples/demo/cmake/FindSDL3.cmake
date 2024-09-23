# FindSDL3.cmake - Find SDL3 libraries and headers

# FindSDL3
# This module finds SDL3 libraries and headers for CMake.

# SDL3_HOME: The root directory where SDL3 is installed.

# Set the default SDL3_HOME if not provided
if(NOT SDL3_HOME)
    set(SDL3_HOME "${CMAKE_CURRENT_LIST_DIR}/lib/SDL3" CACHE PATH "SDL3 installation directory")
endif()

# Find the SDL3 headers
find_path(SDL3_INCLUDE_DIR
    NAMES SDL.h
    PATHS
        ${SDL3_HOME}/include
        /usr/local/include/SDL3
    PATH_SUFFIXES x86_64
)

# Find the SDL3 library
find_library(SDL3_LIBRARY
    NAMES SDL3
    PATHS
        ${SDL3_HOME}/lib
        /usr/local/lib
    PATH_SUFFIXES lib lib64
)

# Check if the headers and libraries were found
if(SDL3_INCLUDE_DIR AND SDL3_LIBRARY)
    set(SDL3_FOUND TRUE)
else()
    set(SDL3_FOUND FALSE)
endif()

# Define the SDL3 package
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL3
    REQUIRED_VARS SDL3_INCLUDE_DIR SDL3_LIBRARY
    VERSION_VAR SDL3_VERSION
)

# Create the SDL3 target
if(SDL3_FOUND)
    add_library(SDL3::SDL3 UNKNOWN IMPORTED)
    set_target_properties(SDL3::SDL3 PROPERTIES
        IMPORTED_LOCATION ${SDL3_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${SDL3_INCLUDE_DIR}
    )

    # Set the libraries and include directories
    set(SDL3_LIBRARIES SDL3::SDL3)
    set(SDL3_INCLUDE_DIRS ${SDL3_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Could not find SDL3 libraries.")
endif()

