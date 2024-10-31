#pragma once
#include <string>

constexpr int ECS_VERSION_MAJOR = 0;
constexpr int ECS_VERSION_MINOR = 1;
constexpr int ECS_VERSION_PATCH = 0;

constexpr int ECS_GLFW_VERSION_MAJOR = 3;
constexpr int ECS_GLFW_VERSION_MINOR = 3;

namespace ECS {
    class Config {
        public:
            static const std::string &getVersion();
            static const std::string &getGLFWVersion();
    };
}