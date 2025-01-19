#pragma once

#include <vector>
#include <functional>
#include <Strake/Component/Renderer/Renderer.hpp>
#include <Strake/Component/Renderer/MeshRenderer.hpp>

namespace Strake {
    class RendererManager {
        public:
            explicit RendererManager(EventDispatcher &eventDispatcher);
            ~RendererManager();
            RendererManager(const RendererManager &other) = delete;
            RendererManager(RendererManager &&other) = delete;
            RendererManager &operator=(const RendererManager &other) = delete;
            RendererManager &operator=(RendererManager &&other) = delete;

            void addRenderer(Renderer &renderer);
            void removeRenderer(Renderer &renderer);
            void clear();
            [[nodiscard]] std::vector<std::reference_wrapper<Renderer>> &getRenderers();
            std::vector<std::reference_wrapper<Renderer>> updateLightings(std::vector<std::reference_wrapper<Light>> &lights);

        private:
            std::vector<std::reference_wrapper<Renderer>> m_renderers;

            EventDispatcher &m_eventDispatcher;
            std::unordered_map<EventDispatcher::EventID, std::string> m_subscriptions;

    };
}