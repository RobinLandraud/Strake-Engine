#version 330 core

layout(location = 0) in vec3 aPos;       // Vertex position
layout(location = 1) in vec2 aTexCoord;   // Texture coordinate

out vec2 TexCoords;  // Output texture coordinates to the fragment shader

uniform mat4 model;      // Model matrix
uniform mat4 view;       // View matrix
uniform mat4 projection; // Projection matrix

void main() {
    // Calculate the vertex position in clip space
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
    // Pass texture coordinates to the fragment shader
    TexCoords = aTexCoord;
}
