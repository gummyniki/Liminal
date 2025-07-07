#include "liminal.h"

namespace cube {
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    class Cube {
        public:
            glm::vec3 position;
            glm::vec3 scale;
            glm::vec3 rotation;
            glm::mat4 model;
            glm::vec3 color; // Default color white
            unsigned int texture;
            bool useColor; // Flag to determine if color should be used

            Cube() {
                model = glm::mat4(1.0f);
                position = glm::vec3(0.0f, 0.0f, 0.0f);
                scale = glm::vec3(1.0f, 1.0f, 1.0f);
                rotation = glm::vec3(0.0f, 0.0f, 0.0f);
                color = glm::vec3(0.0f, 0.0f, 0.0f);
                useColor = false;
            }

            void updateModelMatrix() {
                model = glm::mat4(1.0f);
                model = glm::translate(model, position);
                model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, scale);
            }

            void draw(GLuint shaderProgram) {
                glUniform1i(glGetUniformLocation(shaderProgram, "isModel"), 0);

                int modelLoc = glGetUniformLocation(shaderProgram, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

                int colorLoc = glGetUniformLocation(shaderProgram, "uColor");
                glUniform1i(glGetUniformLocation(shaderProgram, "useColor"), useColor);
                glUniform3fv(colorLoc, 1, glm::value_ptr(color));
                glBindTexture(GL_TEXTURE_2D, texture);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
    
    };

}
