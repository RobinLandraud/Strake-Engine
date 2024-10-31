#include <ECS/init.hpp>

int ECS::init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glDepthFunc(GL_LEQUAL); // Set depth function to less than or equal to 
    glEnable(GL_TEXTURE_2D); // Enable texturing
    glEnable(GL_BLEND); // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function to use alpha values
    glFrontFace(GL_CCW); // Front faces are counter-clockwise
    glEnable(GL_CULL_FACE); // Enable face culling
    glCullFace(GL_BACK); // Cull back faces
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the clear color to black
    glEnable(GL_ALPHA_TEST); // Enable alpha testing
    glAlphaFunc(GL_GREATER, 0.1f); // Render pixels with alpha greater than 0.1
    return 0;
}