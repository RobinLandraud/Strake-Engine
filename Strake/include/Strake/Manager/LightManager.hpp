#pragma once

#include <vector>
#include <functional>
#include <Strake/Component/Light/Light.hpp>
#include <Strake/Component/Renderer/MeshRenderer.hpp>
#include <Strake/Dispatcher/EventDispatcher.hpp>

namespace Strake {
    class LightManager {
        public:
            explicit LightManager(EventDispatcher &eventDispatcher);
            ~LightManager();
            LightManager(const LightManager &other) = delete;
            LightManager(LightManager &&other) = delete;
            LightManager &operator=(const LightManager &other) = delete;
            LightManager &operator=(LightManager &&other) = delete;

            void addLight(Light &light, int priority);
            void removeLight(Light &light, int priority);
            void clear();
            [[nodiscard]] std::vector<std::reference_wrapper<Light>> &getLights(int layer);

            void clearObjects(int layer);
            void renderShadowMaps(int layer, int winWidth, int winHeight);

        private:
            ShaderProgram m_shadowShaderProgram;
            std::map<int, std::vector<std::reference_wrapper<Light>>> m_lights;

            EventDispatcher &m_eventDispatcher;
            std::unordered_map<EventDispatcher::EventID, std::string> m_subscriptions;
    };
}