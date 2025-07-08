#include "liminal.h"

namespace cube {
    extern float vertices[180];

    class Cube {
        public:
            glm::vec3 position;
            glm::vec3 scale;
            glm::vec3 rotation;
            glm::mat4 model;
            glm::vec3 color; // Default color white
            unsigned int texture;
            bool useColor; // Flag to determine if color should be used


            void updateModelMatrix();

            void draw();
    
    };

}
