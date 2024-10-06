#include "config.hpp"
#include <SFML/Config.hpp>

namespace ECS {
    const std::string &Config::getVersion() {
        static const std::string version = std::to_string(ECS_VERSION_MAJOR) + "." + std::to_string(ECS_VERSION_MINOR) + "." + std::to_string(ECS_VERSION_PATCH);
        return version;
    }
    const std::string &Config::getSFMLVersion() {
        static const std::string version = std::to_string(SFML_VERSION_MAJOR) + "." + std::to_string(SFML_VERSION_MINOR) + "." + std::to_string(SFML_VERSION_PATCH);
        return version;
    }
}