# FindSDL3_IMAGE.cmake - Find SDL3_image libraries and headers

# FindSDL3_IMAGE
# This module finds SDL3_image libraries and headers for CMake.

# SDL3_IMAGE_HOME: The root directory where SDL3_image is installed.

# Set the default SDL3_IMAGE_HOME if not provided
if(NOT SDL3_IMAGE_HOME)
    set(SDL3_IMAGE_HOME "${CMAKE_CURRENT_LIST_DIR}/lib/SDL3_image" CACHE PATH "SDL3_image installation directory")
endif()

# Find the SDL3_image headers
find_path(SDL3_IMAGE_INCLUDE_DIR
    NAMES SDL_image.h
    PATHS
        ${SDL3_IMAGE_HOME}/include
        /usr/local/include/SDL3_image
    PATH_SUFFIXES x86_64
)

# Find the SDL3_image library
find_library(SDL3_IMAGE_LIBRARY
    NAMES SDL3_image
    PATHS
        ${SDL3_IMAGE_HOME}/lib
        /usr/local/lib
    PATH_SUFFIXES lib lib64
)

# Check if the headers and libraries were found
if(SDL3_IMAGE_INCLUDE_DIR AND SDL3_IMAGE_LIBRARY)
    set(SDL3_IMAGE_FOUND TRUE)
else()
    set(SDL3_IMAGE_FOUND FALSE)
endif()

# Define the SDL3_image package
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL3_image
    REQUIRED_VARS SDL3_IMAGE_INCLUDE_DIR SDL3_IMAGE_LIBRARY
    VERSION_VAR SDL3_IMAGE_VERSION
)

# Create the SDL3_image target
if(SDL3_IMAGE_FOUND)
    add_library(SDL3_image::SDL3_image UNKNOWN IMPORTED)
    set_target_properties(SDL3_image::SDL3_image PROPERTIES
        IMPORTED_LOCATION ${SDL3_IMAGE_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${SDL3_IMAGE_INCLUDE_DIR}
    )

    # Set the libraries and include directories
    set(SDL3_IMAGE_LIBRARIES SDL3_image::SDL3_image)
    set(SDL3_IMAGE_INCLUDE_DIRS ${SDL3_IMAGE_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Could not find SDL3_image libraries.")
endif()

