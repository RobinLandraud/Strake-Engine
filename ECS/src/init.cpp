#include <ECS/init.hpp>

#define GL_CHECK(stmt) do { \
    stmt; \
    if (glGetError() != GL_NO_ERROR) { \
        std::cerr << "OpenGL error at " << __FILE__ << ":" << __LINE__ << " - " << #stmt << std::endl; \
        return 1; \
    } \
} while (0)

int ECS::init() {
    GL_CHECK(glEnable(GL_DEPTH_TEST)); // Enable depth testing for 3D rendering (occlusion culling)
    GL_CHECK(glDepthFunc(GL_LEQUAL)); // Set depth function to less than or equal to
    //GL_CHECK(glEnable(GL_TEXTURE_2D)); // replaced with sampler2D in shader
    GL_CHECK(glEnable(GL_BLEND)); // Enable blending
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Set blending function to use alpha values
    GL_CHECK(glFrontFace(GL_CCW)); // Front faces are counter-clockwise
    GL_CHECK(glEnable(GL_CULL_FACE)); // Enable face culling
    GL_CHECK(glCullFace(GL_BACK)); // Cull back faces
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f)); // Set the clear color to black
    //GL_CHECK(glEnable(GL_ALPHA_TEST)); // will be replaced with discard in shader
    //GL_CHECK(glAlphaFunc(GL_GREATER, 0.1f)); // Render pixels with alpha greater than 0.1
    return 0;
}