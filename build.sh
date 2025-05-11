#!/bin/bash

echo "Cleaning build directory..."
rm -rf build/*
mkdir -p build

echo "Configuring project with CMake..."
cmake -S . -B build

echo "Building project..."
cmake --build build

./build/OpenGLProject