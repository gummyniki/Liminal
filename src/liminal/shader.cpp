#include "../headers/glad/gl.h"
#include <GLFW/glfw3.h>
#include <iostream>

enum SHADERTYPE { VERTEX_SHADER, FRAGMENT_SHADER };

namespace shader {
GLuint createShader(SHADERTYPE shaderType, const char *source) {
  GLuint newShader;

  if (shaderType == VERTEX_SHADER) {
    newShader = glCreateShader(GL_VERTEX_SHADER);

  } else if (shaderType == FRAGMENT_SHADER) {
    newShader = glCreateShader(GL_FRAGMENT_SHADER);
  } else {
    newShader = glCreateShader(GL_VERTEX_SHADER);
  }

  glShaderSource(newShader, 1, &source, NULL);
  glCompileShader(newShader);

  int success;
  char infoLog[512];
  glGetShaderiv(newShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(newShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  return newShader;
}
GLuint createShaderProgram(GLuint vs, GLuint fs) {
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vs);
  glAttachShader(shaderProgram, fs);
  glLinkProgram(shaderProgram);

  glDeleteShader(vs);
  glDeleteShader(fs);

  int success;
  char infoLog[512];

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  return shaderProgram;
}

const char *readFile(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    std::cout << "Failed to open shader file: " << filename << std::endl;
    return nullptr;
  }
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = new char[length + 1];
  fread(buffer, 1, length, file);
  buffer[length] = '\0';
  fclose(file);

  return buffer;
}

} 
