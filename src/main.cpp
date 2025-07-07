
#include "liminal/liminal.h"
#include "liminal/imGuiSetup.h"
#include "liminal/shader.h"
#include "liminal/texture.h"
#include "liminal/window.h"
#include "liminal/cube.h"
#include "liminal/openGLObjects.h"
#include "liminal/imGuiSetup.h"
#include "liminal/world.h"
#include "liminal/camera.h"
#include "liminal/model.h"
#include <iostream>

Camera mainCamera(glm::vec3(0.0f, 0.0f, 3.0f));







int main() {
  liminal::init();
  liminal::camera = mainCamera;
  liminal::camera.Zoom = 90.0f;
  
  liminal::camera.MouseSensitivity = 0.2f;
  
  liminal::setupShaders();
  GLuint VAO = OpenGLObjects::createVAO(cube::vertices, sizeof(cube::vertices));


  liminal::PointLight pointLight1;
  pointLight1.position = glm::vec3(1.2f, 1.0f, 2.0f);
  pointLight1.color = glm::vec3(1.0f, 1.0f, 1.0f);
  pointLight1.constant = 1.0f;
  pointLight1.linear = 0.09f;
  pointLight1.quadratic = 0.032f;


  liminal::PointLight pointLight2;
  pointLight2.position = glm::vec3(-1.2f, -1.0f, -2.0f);
  pointLight2.color = glm::vec3(1.0f, 0.5f, 0.5f);
  pointLight2.constant = 1.0f;
  pointLight2.linear = 0.09f;
  pointLight2.quadratic = 0.032f;
 
  liminal::pointLights.push_back(pointLight1);
  liminal::pointLights.push_back(pointLight2);

  std::vector<liminal::PointLight> pointLightsG;
  pointLightsG.push_back(pointLight1);
  pointLightsG.push_back(pointLight2);

  liminal::createPointLights(pointLightsG);


  cube::Cube cube;
  cube.position = glm::vec3(-0.5f, -0.5f, -0.5f);
  cube.useColor = false;

  liminal::setup_postProcessing();
  liminal::render_postProcessingQuad();
  
  liminal::camera.Zoom = 90.0f;
  

  unsigned int texture = texture::loadTexture("container.jpg");
  cube.texture = liminal::texColorBuffer;

  liminal::initVAO();

  Model ourModel("backpack/backpack.obj", true, true);
  ourModel.position = glm::vec3(0.5f, 0.2f, 0.0f);
  ourModel.scale = glm::vec3(0.5f);
  ourModel.rotation = glm::vec3(0.0f);

  Model model2("Snorkel/snorkel.obj", true, false);
  model2.position = glm::vec3(-0.8f, -0.5f, 0.0f);
  model2.scale = glm::vec3(0.05f);


  // Initialize ImGui
  imguiSetup::setup(liminal::gameWindow);


  while (!glfwWindowShouldClose(liminal::gameWindow)) {
    glBindFramebuffer(GL_FRAMEBUFFER, liminal::framebuffer);
    glEnable(GL_DEPTH_TEST);
    liminal::setup3D();

    liminal::processInput(liminal::gameWindow);

    // Clear your framebuffer (do it after bind)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Start ImGui frame
    imguiSetup::start("Hello, ImGui!");
    ImGui::Checkbox("postprocessing", &liminal::postProcessingEnabled);
    ImGui::Text("This is an example window!");
    if (ImGui::Button("Close")) {
        glfwSetWindowShouldClose(liminal::gameWindow, GLFW_TRUE);
    }
    ImGui::End();

    // Render your 3D scene here
    liminal::prepRendering(liminal::shaderProgram, VAO);
    liminal::setupLights();

    // Update and draw objects
    cube.rotation.x = glm::radians(45.0f) * (float)glfwGetTime();
    cube.updateModelMatrix();
    cube.draw(liminal::shaderProgram);

    ourModel.rotation.y = glm::radians(800.0f) * (float)glfwGetTime();
    ourModel.Draw(liminal::shaderProgram);

    model2.Draw(liminal::shaderProgram);

    // Unbind framebuffer (switch to default framebuffer, screen)
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // Disable depth test for screen quad / blit

    // Reset viewport to window size
    int width, height;
    glfwGetFramebufferSize(liminal::gameWindow, &width, &height);
    glViewport(0, 0, width, height);

    // Now choose whether to do postprocessing or blit
    if (liminal::postProcessingEnabled) {
        liminal::render_postProcessing();  // draws fullscreen quad with shader
    } else {
        liminal::blitFrameBuffer(); // blit framebuffer to default framebuffer
    }

    glEnable(GL_DEPTH_TEST); // Re-enable depth test for next frame

    // Render ImGui on top (still on default framebuffer)
    imguiSetup::render();

    liminal::postRendering();
}


  liminal::cleanup();
  
  return 0;
}

