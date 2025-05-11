cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 17)

# --------------------------
# Source files
# --------------------------
file(GLOB_RECURSE SRC_FILES src/*.cpp)

# --------------------------
# ImGui
# --------------------------
set(IMGUI_DIR "third_party/imgui")
set(IMGUI_BACKEND_DIR "${IMGUI_DIR}/backends")

# Manually include only required ImGui source files
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_BACKEND_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.cpp
)

list(APPEND SRC_FILES ${IMGUI_SOURCES})

# --------------------------
# Create executable
# --------------------------
add_executable(${PROJECT_NAME} ${SRC_FILES})

# --------------------------
# Dependencies
# --------------------------
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)

# --------------------------
# Include directories
# --------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${IMGUI_DIR}
    ${IMGUI_BACKEND_DIR}
)

# --------------------------
# Link libraries
# --------------------------
target_link_libraries(${PROJECT_NAME}
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
    OpenGL::GL
    dl
    pthread
    X11
)
