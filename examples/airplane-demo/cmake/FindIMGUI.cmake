# FindIMGUI.cmake
# Locate Dear ImGui and set up necessary variables and targets

# Specify the path to ImGui (adjust if needed)
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../external/imgui)

# Locate the main ImGui source files
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
)

# Add a target for Dear ImGui
add_library(IMGUI STATIC ${IMGUI_SOURCES})

# Set include directories
target_include_directories(IMGUI PUBLIC 
    ${IMGUI_DIR} 
    ${IMGUI_DIR}/backends
)

# Export IMGUI target
set(IMGUI_FOUND TRUE)
set(IMGUI_INCLUDE_DIRS ${IMGUI_DIR} ${IMGUI_DIR}/backends)
set(IMGUI_LIBRARIES IMGUI)

