# OpenGL ImGui Project

This is a simple OpenGL project using [GLFW](https://www.glfw.org/), [GLEW](http://glew.sourceforge.net/), and [Dear ImGui](https://github.com/ocornut/imgui) for GUI rendering. The goal is to provide a minimal, modular, and cross-platform base for OpenGL applications with ImGui support.

## Features

- OpenGL window with context created via GLFW
- GLEW for loading OpenGL extensions
- ImGui GUI rendered using OpenGL3 + GLFW backend
- Modular structure (`window.cpp`, etc.)
- CMake-based build system

WARNING, currently git is being very annoying and the source files for imgui are not being pushed, so just go to the original imgui website, copy all of the source files and paste them in `third_party/imgui`

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
chmod +x build.sh
./build.sh

```

