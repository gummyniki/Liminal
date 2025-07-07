#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D screenTexture;

void main()
{
    vec3 color = texture(screenTexture, TexCoord).rgb;
    float gray = dot(color, vec3(0.2126, 0.7152, 0.0722)); // luminance
    FragColor = vec4(vec3(gray), 1.0);

    //FragColor = vec4(0.0, 1.0, 0.0, 1.0); // green color for testing
}
