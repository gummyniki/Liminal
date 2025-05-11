# OpenGL ImGui Project

This is a simple OpenGL project using [GLFW](https://www.glfw.org/), [GLEW](http://glew.sourceforge.net/), and [Dear ImGui](https://github.com/ocornut/imgui) for GUI rendering. The goal is to provide a minimal, modular, and cross-platform base for OpenGL applications with ImGui support.

## Features

- OpenGL window with context created via GLFW
- GLEW for loading OpenGL extensions
- ImGui GUI rendered using OpenGL3 + GLFW backend
- Modular structure (`window.cpp`, etc.)
- CMake-based build system

## Prerequisites

### Linux

Install dependencies (example for Arch Linux):

```bash
sudo pacman -S glfw glew cmake
```
### Windows

Use a package manager like vcpkg or manually install:
+ GLEW
+ GLFW
+ OpenGL (usually comes with drivers)

• make sure the dependencies are discoverable by CMake!
  
## Building the project

```bash
git clone https://github.com/yourusername/opengl-imgui-project.git
cd opengl-imgui-project
cmake -B build
cmake --build build
./build/OpenGLProject
```

