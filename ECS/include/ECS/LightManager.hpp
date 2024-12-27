#include <vector>
#include <functional>
#include <ECS/Lights.hpp>
#include <ECS/MeshRenderer.hpp>
#include <ECS/EventDispatcher.hpp>

namespace ECS {
    class LightManager {
        public:
            explicit LightManager(EventDispatcher &eventDispatcher);
            ~LightManager() = default;
            LightManager(const LightManager &other) = delete;
            LightManager(LightManager &&other) = delete;
            LightManager &operator=(const LightManager &other) = delete;
            LightManager &operator=(LightManager &&other) = delete;

            void addLight(Light &light);
            void removeLight(Light &light);
            void clear();
            [[nodiscard]] std::vector<std::reference_wrapper<Light>> &getLights();

        private:
            std::vector<std::reference_wrapper<Light>> m_lights;
            EventDispatcher &m_eventDispatcher;
    };
}