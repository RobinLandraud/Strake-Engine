#include <Strake/Config/Config.hpp>
#include <GL/glew.h>    // ou <GL/gl.h> si pas GLEW
#include <iostream>

namespace Strake {
    const std::string &Config::getVersion() {
        static const std::string version = std::to_string(ECS_VERSION_MAJOR) + "." + std::to_string(ECS_VERSION_MINOR) + "." + std::to_string(ECS_VERSION_PATCH);
        return version;
    }
    const std::string &Config::getGLFWVersion() {
        static const std::string version = std::to_string(ECS_GLFW_VERSION_MAJOR) + "." + std::to_string(ECS_GLFW_VERSION_MINOR);
        return version;
    }
}