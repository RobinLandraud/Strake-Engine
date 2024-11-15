#version 330 core

in vec2 TexCoords;        // Texture coordinates from the vertex shader
out vec4 FragColor;       // Output fragment color

uniform sampler2D textureSampler; // Texture sampler

void main() {
    // Sample the texture at the given coordinates
    FragColor = texture(textureSampler, TexCoords);
}
