#include "liminal.h"



namespace OpenGLObjects {
GLuint createVBO(float vertices[], size_t size) {
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  return VBO;
}

GLuint createVAO(float vertices[], size_t size) {
  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  GLuint VBO = createVBO(vertices, size);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  return VAO;
}

GLuint createEBO(unsigned int indices[], size_t size) {
  GLuint EBO;
  glGenBuffers(1, &EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

  return EBO;
}

} // namespace OpenGLObjects
