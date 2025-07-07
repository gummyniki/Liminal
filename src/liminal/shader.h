#include "../headers/glad/gl.h"
#include <GLFW/glfw3.h>

enum SHADERTYPE { VERTEX_SHADER, FRAGMENT_SHADER };

namespace shader {
GLuint createShader(SHADERTYPE shaderType, const char *source);
GLuint createShaderProgram(GLuint vs, GLuint fs);
const char *readFile(const char *filename);
} // namespace shader
