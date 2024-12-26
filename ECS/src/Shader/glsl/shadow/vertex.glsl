#version 330 core

layout(location = 0) in vec3 aPos; // Vertex position
layout(location = 1) in vec3 aNormal; // Normal (optional)

uniform mat4 lightSpaceMatrix; // Light's view-projection matrix

void main() {
    // Transform vertex position to light's space
    gl_Position = lightSpaceMatrix * vec4(aPos, 1.0); 
}