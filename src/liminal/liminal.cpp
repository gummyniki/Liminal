#include "liminal.h"
#include "shader.h"
#include "camera.h"

namespace liminal {
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
GLFWwindow *gameWindow = nullptr;
glm::mat4 projection;
glm::mat4 view;
GLuint shaderProgram;
GLuint lightVAO;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
Camera camera;
bool postProcessingEnabled = false;


float quadVertices[] = {
    // positions   // texCoords
    -1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f,

    -1.0f,  1.0f,  0.0f, 1.0f,
     1.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 1.0f
};


GLuint quadVAO;
GLuint quadVBO;
unsigned int framebuffer;
unsigned int rbo;
unsigned int texColorBuffer;
GLuint postProcessingShaderProgram;


std::vector<PointLight> pointLights;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        liminal::camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        liminal::camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        liminal::camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        liminal::camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    // Resize framebuffer attachments
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}



void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (liminal::firstMouse)
    {
        liminal::lastX = xpos;
        liminal::lastY = ypos;
        liminal::firstMouse = false;
    }

    float xoffset = xpos - liminal::lastX;
    float yoffset = liminal::lastY - ypos; // reversed since y-coordinates go from bottom to top

    liminal::lastX = xpos;
    liminal::lastY = ypos;

    liminal::camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    liminal::camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

int init() {
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    gameWindow = window::init("Hello, ImGui!", SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPosCallback(gameWindow, mouse_callback);
    glfwSetFramebufferSizeCallback(gameWindow, framebuffer_size_callback);
    glfwSetScrollCallback(gameWindow, scroll_callback);





    return 0;
}

void cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window::shutdown(gameWindow);
}

void initVAO() {
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void setupShaders() {
    const char *vertexShaderSource = shader::readFile("shaders/shader.vert");
    const char *fragmentShaderSource = shader::readFile("shaders/shader.frag");

    GLuint vs = shader::createShader(SHADERTYPE::VERTEX_SHADER, vertexShaderSource);
    GLuint fs = shader::createShader(SHADERTYPE::FRAGMENT_SHADER, fragmentShaderSource);

    delete[] vertexShaderSource;
    delete[] fragmentShaderSource;
    shaderProgram = shader::createShaderProgram(vs, fs);
}

void createPointLights(std::vector<PointLight> &lights) {
    if (lights.size() < 8) {
        for (const auto &light : lights) {
            pointLights.push_back(light);
        }
    }
}

void setupLights() {
    glUniform1i(glGetUniformLocation(shaderProgram, "numPointLights"), pointLights.size());

    for (size_t i = 0; i < pointLights.size(); ++i) {
        std::string index = std::to_string(i);
        glUniform3fv(glGetUniformLocation(shaderProgram, ("pointLights[" + index + "].position").c_str()), 1, glm::value_ptr(pointLights[i].position));
        glUniform3fv(glGetUniformLocation(shaderProgram, ("pointLights[" + index + "].color").c_str()), 1, glm::value_ptr(pointLights[i].color));
        glUniform1f(glGetUniformLocation(shaderProgram, ("pointLights[" + index + "].constant").c_str()), pointLights[i].constant);
        glUniform1f(glGetUniformLocation(shaderProgram, ("pointLights[" + index + "].linear").c_str()), pointLights[i].linear);
        glUniform1f(glGetUniformLocation(shaderProgram, ("pointLights[" + index + "].quadratic").c_str()), pointLights[i].quadratic);
    }
}



void setup_postProcessing() {


    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // create texture to render to
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // create renderbuffer for depth and stencil
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    postProcessingShaderProgram = shader::createShaderProgram(
        shader::createShader(SHADERTYPE::VERTEX_SHADER, shader::readFile("shaders/screen_quad.vert")),
        shader::createShader(SHADERTYPE::FRAGMENT_SHADER, shader::readFile("shaders/grayscale.frag"))
    );
    
}


void updatePostProcessing(const char* newShaderPath) {
    postProcessingShaderProgram = shader::createShaderProgram(
        shader::createShader(SHADERTYPE::VERTEX_SHADER, shader::readFile("shaders/screen_quad.vert")),
        shader::createShader(SHADERTYPE::FRAGMENT_SHADER, shader::readFile(newShaderPath))
    );
}

void render_postProcessingQuad() {
    
    float quadVertices[] = {
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    // position attribute (2 floats)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texCoords attribute (2 floats)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

void render_postProcessing() {
    

    
    glDisable(GL_DEPTH_TEST); // Disable depth test for post-processing
    glClear(GL_COLOR_BUFFER_BIT);


    glUseProgram(liminal::postProcessingShaderProgram);

    glBindVertexArray(liminal::quadVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, liminal::texColorBuffer);
    glUniform1i(glGetUniformLocation(liminal::postProcessingShaderProgram, "screenTexture"), 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glEnable(GL_DEPTH_TEST); // Re-enable depth test for 3D rendering
}

void blitFrameBuffer() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, liminal::framebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, liminal::SCREEN_WIDTH, liminal::SCREEN_HEIGHT,
                          0, 0, liminal::SCREEN_WIDTH, liminal::SCREEN_HEIGHT,
                          GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void setup3D() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
    view = liminal::camera.GetViewMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void prepRendering(GLuint shaderProgram, GLuint VAO) {
    glUseProgram(shaderProgram);
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    // glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    
    glBindVertexArray(VAO);
}

void postRendering() {
    glBindVertexArray(0);
    glfwPollEvents();

    glfwSwapBuffers(gameWindow);
}



}
