#version 330 core

in vec2 TexCoords;        // Texture coordinates from the vertex shader
out vec4 FragColor;       // Output fragment color

uniform sampler2D textureSampler; // Texture sampler
uniform float alphaThreshold;     // Alpha threshold for the test

void main() {
    // Sample the texture at the given coordinates
    vec4 texColor = texture(textureSampler, TexCoords);

    // Discard the fragment if the alpha value is below the threshold
    if (texColor.a < alphaThreshold) {
        discard;
    }

    // Set the output fragment color
    FragColor = texColor;
}
