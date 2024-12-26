#include <ECS/init.hpp>

#define GL_CHECK(stmt) do { \
    stmt; \
    if (glGetError() != GL_NO_ERROR) { \
        std::cerr << "OpenGL error at " << __FILE__ << ":" << __LINE__ << " - " << #stmt << std::endl; \
        return 1; \
    } \
} while (0)

void GLAPIENTRY OpenGLDebugCallback(GLenum source, GLenum type, GLuint id,
                                    GLenum severity, GLsizei length,
                                    const GLchar* message, const void* userParam) {
    std::cerr << "OpenGL Debug Message:\n";
    std::cerr << "Source: ";
    switch (source) {
        case GL_DEBUG_SOURCE_API:             std::cerr << "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Other"; break;
    }
    std::cerr << "\nType: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               std::cerr << "Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Deprecated Behavior"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cerr << "Undefined Behavior"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cerr << "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cerr << "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cerr << "Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cerr << "Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cerr << "Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cerr << "Other"; break;
    }
    std::cerr << "\nID: " << id << "\n";
    std::cerr << "Severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "High"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Notification"; break;
    }
    std::cerr << "\nMessage: " << message << "\n\n";

    // Optional: Break on critical errors
    if (severity == GL_DEBUG_SEVERITY_HIGH) {
        __debugbreak(); // use '__debugbreak()' for MSVC and '__builtin_trap()' for GCC/Clang)
    }
}

int ECS::init() {
    GL_CHECK(glEnable(GL_DEPTH_TEST)); // Enable depth testing for 3D rendering (occlusion culling)
    GL_CHECK(glDepthFunc(GL_LESS)); // Set depth function to less than or equal to
    GL_CHECK(glEnable(GL_BLEND)); // Enable blending
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)); // Set blending function to use alpha values
    GL_CHECK(glFrontFace(GL_CCW)); // Front faces are counter-clockwise
    GL_CHECK(glEnable(GL_CULL_FACE)); // Enable face culling
    GL_CHECK(glCullFace(GL_BACK)); // Cull back faces
    GL_CHECK(glClearColor(0.0f, 0.0f, 0.0f, 1.0f)); // Set the clear color to black
    // Enable debug output
    GL_CHECK(glEnable(GL_DEBUG_OUTPUT));
    GL_CHECK(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));
    GL_CHECK(glDebugMessageCallback(OpenGLDebugCallback, nullptr));
    return 0;
}

int ECS::exit() {
    glfwTerminate();
    return 0;
}