#include "liminal.h"

namespace postProcessing {

    enum effectType {
        CHROMATIC_ABERRATION,
        GRAYSCALE,
        SEPIA,
        VIGNETTE
    };

    class PostProcessingEffect {
        public:
            const char* shaderPath;
            effectType type;
            glm::vec2 offset;
            const char* offsetUniformName;


        void applyEffect() {

            liminal::updatePostProcessing(shaderPath);
        }


        void updateEffect() {
            glUniform2f(glGetUniformLocation(liminal::postProcessingShaderProgram, offsetUniformName), offset.x, offset.y);
        }

        

    };
}