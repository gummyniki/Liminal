#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include "window.h"
#include "camera.h"
#include <vector>


namespace liminal {
    extern int SCREEN_WIDTH;
    extern int SCREEN_HEIGHT;
    extern GLFWwindow *gameWindow;
    extern glm::mat4 projection;
    extern glm::mat4 view;
    extern GLuint shaderProgram;
    extern float deltaTime;
    extern float lastFrame;
    extern float lastX;
    extern float lastY;
    extern int LIMINAL_MAX_LIGHTS;
    extern bool firstMouse;
    extern Camera camera;
    extern GLuint lightVAO;
    extern GLuint VAO;
    struct PointLight {
        glm::vec3 position;
        glm::vec3 color;

        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;

        bool debug = false;
    };


    extern float quadVertices[];

    extern GLuint quadVAO;
    extern GLuint quadVBO;
    extern unsigned int framebuffer;
    extern unsigned int rbo;
    extern unsigned int texColorBuffer;
    extern GLuint postProcessingShaderProgram;
    extern bool postProcessingEnabled;

    extern std::vector<PointLight> pointLights;

    int init();
    void cleanup();
    void initVAO();
    void setup3D();
    void prepRendering(GLuint VAO);
    void postRendering();
    void setupShaders();
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void createPointLights(std::vector<PointLight> &lights);
    void setupLights();

    void setup_postProcessing();
    void updatePostProcessing(const char* newShaderPath);
    void render_postProcessingQuad();
    void render_postProcessing();
    void blitFrameBuffer();


    bool isKeyPressed(int key);
    bool windowShouldClose();
}
