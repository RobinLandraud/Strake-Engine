#version 330 core

layout(location = 0) in vec3 aPos; // Position attribute of the collider mesh

uniform mat4 model;       // Model matrix
uniform mat4 view;        // View matrix
uniform mat4 projection;  // Projection matrix

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}