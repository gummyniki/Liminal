#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

namespace window
{
    GLFWwindow* init(std::string title, int width, int height) {
        GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test", nullptr, nullptr);
            if (!window) {
                std::cerr << "Failed to create window\n";
                glfwTerminate();
            }

        

    glfwMakeContextCurrent(window);
    return window;

    }
    void update() {

    }

    void shutdown(GLFWwindow* window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    
}