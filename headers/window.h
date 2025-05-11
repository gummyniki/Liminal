#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace window {
    GLFWwindow* init(std::string title, int width, int height);
    
    void shutdown(GLFWwindow* window);
}