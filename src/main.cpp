#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


#include <window.h>
#include <imGuiSetup.h>


int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    GLFWwindow* window = window::init("Hello, ImGui!", 800, 600);

    glewInit();

    // Initialize ImGui
    imguiSetup::setup(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the ImGui frame
        imguiSetup::start("Hello, ImGui!");

        ImGui::Text("This is an example window!");
        if (ImGui::Button("Close")) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        ImGui::End();

        // Render OpenGL content
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render ImGui
        imguiSetup::render();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window::shutdown(window);
    return 0;
}
