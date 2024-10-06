#include <string>

constexpr int ECS_VERSION_MAJOR = 0;
constexpr int ECS_VERSION_MINOR = 1;
constexpr int ECS_VERSION_PATCH = 0;

namespace ECS {
    class Config {
        public:
            static const std::string &getVersion();
            static const std::string &getSFMLVersion();
    };
}