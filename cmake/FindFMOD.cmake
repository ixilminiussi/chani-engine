# FindFMOD.cmake - Find FMOD libraries and headers

# FindFMOD
# This module finds FMOD libraries and headers for CMake.

# FMOD_HOME: The root directory where FMOD is installed.

# Set the default FMOD_HOME if not provided
if(NOT FMOD_HOME)
    set(FMOD_HOME "${CMAKE_CURRENT_LIST_DIR}/lib/fmodstudioapi20223linux/fmod" CACHE PATH "FMOD installation directory")
endif()

# Find the FMOD Studio headers
find_path(FMOD_STUDIO_INCLUDE_DIR
    NAMES fmod_studio.hpp
    PATHS
        ${FMOD_HOME}/studio/inc
        /usr/local/include/fmod/studio
)

# Find the FMOD Core headers
find_path(FMOD_CORE_INCLUDE_DIR
    NAMES fmod.h
    PATHS
        ${FMOD_HOME}/core/inc
        /usr/local/include/fmod/core
)

# Check if the include directories were found
if(FMOD_STUDIO_INCLUDE_DIR AND FMOD_CORE_INCLUDE_DIR)
    set(FMOD_INCLUDE_DIRS
        ${FMOD_STUDIO_INCLUDE_DIR}
        ${FMOD_CORE_INCLUDE_DIR}
    )
else()
    set(FMOD_INCLUDE_DIRS)
endif()

# Find the FMOD Studio library
find_library(FMOD_STUDIO_LIBRARY
    NAMES fmodstudio
    PATHS
        ${FMOD_HOME}/studio/lib
        /usr/local/lib/fmod/studio
    PATH_SUFFIXES x86_64
)

# Find the FMOD Core library
find_library(FMOD_CORE_LIBRARY
    NAMES fmod
    PATHS
        ${FMOD_HOME}/core/lib
        /usr/local/lib/fmod/core
    PATH_SUFFIXES x86_64
)

# Check if the libraries were found
if(FMOD_STUDIO_LIBRARY AND FMOD_CORE_LIBRARY)
    set(FMOD_LIBRARIES
        ${FMOD_STUDIO_LIBRARY}
        ${FMOD_CORE_LIBRARY}
    )
else()
    set(FMOD_LIBRARIES)
endif()

# Define the FMOD package
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FMOD
    REQUIRED_VARS FMOD_INCLUDE_DIRS FMOD_LIBRARIES
    VERSION_VAR FMOD_VERSION
)

# Create the targets for FMOD
if(FMOD_FOUND)
    add_library(FMOD::Core UNKNOWN IMPORTED)
    set_target_properties(FMOD::Core PROPERTIES
        IMPORTED_LOCATION ${FMOD_CORE_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${FMOD_CORE_INCLUDE_DIR}
    )

    add_library(FMOD::Studio UNKNOWN IMPORTED)
    set_target_properties(FMOD::Studio PROPERTIES
        IMPORTED_LOCATION ${FMOD_STUDIO_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${FMOD_STUDIO_INCLUDE_DIR}
    )

    # Set the targets and include directories
    set(FMOD_LIBRARIES FMOD::Core FMOD::Studio)
    set(FMOD_INCLUDE_DIRS ${FMOD_CORE_INCLUDE_DIR} ${FMOD_STUDIO_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Could not find FMOD libraries.")
endif()

