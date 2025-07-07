#version 330 core
out vec4 FragColor;

uniform sampler2D screenTexture;

uniform vec2 u_offset;

in vec2 TexCoord;

void main() {
    vec2 uv = TexCoord;

    float offsetAmount = 0.003; // Play with this for intensity
    vec2 offset = u_offset * offsetAmount;

    // Sample each channel at slightly different UVs
    float r = texture(screenTexture, uv + offset).r;
    float g = texture(screenTexture, uv).g;
    float b = texture(screenTexture, uv - offset).b;

    FragColor = vec4(r, g, b, 1.0);
}
