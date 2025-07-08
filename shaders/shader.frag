#version 330 core
#define MAX_LIGHTS 200

struct PointLight {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

uniform PointLight pointLights[MAX_LIGHTS];
uniform int numPointLights;

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform sampler2D texture_diffuse1;

uniform vec3 uColor;
uniform bool useColor;
uniform bool isModel;

uniform vec3 uViewPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lighting = vec3(0.0);

    for (int i = 0; i < numPointLights; ++i) {
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * pointLights[i].color;

        vec3 lightDir = normalize(pointLights[i].position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * pointLights[i].color;

        float distance = length(pointLights[i].position - FragPos);
        float attenuation = 1.0 / (pointLights[i].constant + pointLights[i].linear * distance + pointLights[i].quadratic * (distance * distance));

        float specularStrength = 0.5;
        vec3 viewDir = normalize(uViewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * pointLights[i].color;

        lighting += (ambient + diffuse + specular) * attenuation;
    }

    if (!useColor) {
        if (isModel) {
            vec3 textureColor = texture(texture_diffuse1, TexCoord).rgb;
            FragColor = vec4(textureColor * lighting, 1.0);
        } else {
            vec3 textureColor = texture(ourTexture, TexCoord).rgb;
            FragColor = vec4(textureColor * lighting, 1.0);
        }
    } else {
        FragColor = vec4(uColor * lighting, 1.0);
    }
}
