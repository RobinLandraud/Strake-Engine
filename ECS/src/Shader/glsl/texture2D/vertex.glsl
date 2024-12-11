#version 330 core

layout(location = 0) in vec3 aPos;       // Vertex position
layout(location = 1) in vec2 aTexCoord;   // Texture coordinate
layout(location = 2) in vec3 aNormal;     // Normal

out vec2 TexCoords;  // Output texture coordinates to the fragment shader
out vec3 FragPos;    // Output fragment position in world space to the fragment shader
out vec3 Normal;     // Output normal in world space to the fragment shader

uniform mat4 model;      // Model matrix
uniform mat4 view;       // View matrix
uniform mat4 projection; // Projection matrix

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0)); // Get the vertex position in world space
    Normal = mat3(transpose(inverse(model))) * aNormal; // Get the normal in world space
    gl_Position = projection * view * vec4(FragPos, 1.0); // Get the vertex position in screen space
    TexCoords = aTexCoord; // Pass the texture coordinates to the fragment shader
}
