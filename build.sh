#!/bin/bash

# Detect operating system
OS="$(uname -s)"
BUILD_DIR="build"

# Function to clean the build directory
clean_build_dir() {
    echo "Cleaning build directory..."
    rm -rf $BUILD_DIR/*
    mkdir -p $BUILD_DIR
}

# Function to configure and build the project
build_project() {
    echo "Configuring project with CMake..."
    cmake -S . -B $BUILD_DIR

    echo "Building project..."
    cmake --build $BUILD_DIR
}

# Function to run the project
run_project() {
    if [[ -f "$BUILD_DIR/OpenGLProject" ]]; then
        echo "Running the project..."
        ./$BUILD_DIR/OpenGLProject
    else
        echo "Build failed or executable not found!"
    fi
}

# Check the OS and run appropriate commands
if [[ "$OS" == "MINGW"* || "$OS" == "MSYS"* || "$OS" == "CYGWIN"* ]]; then
    # Windows (MSYS2, MinGW, or Cygwin)
    echo "Windows detected"
    clean_build_dir
    build_project
    run_project
elif [[ "$OS" == "Darwin" ]]; then
    # macOS
    echo "macOS detected"
    clean_build_dir
    build_project
    run_project
else
    # Linux
    echo "Linux detected"
    clean_build_dir
    build_project
    run_project
fi
