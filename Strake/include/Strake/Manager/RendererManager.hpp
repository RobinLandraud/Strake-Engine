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
            void moveRenderer(Renderer &renderer, int oldLayer);
            void clear();
            void clearDepth() const;
            [[nodiscard]] std::vector<std::reference_wrapper<Renderer>> &getRenderers(int layer);
            [[nodiscard]] std::map<int, std::vector<std::reference_wrapper<Renderer>>> &getRenderers();

            std::vector<std::reference_wrapper<Renderer>> updateLightings(int layer, std::vector<std::reference_wrapper<Light>> &lights);

        private:
            std::map<int, std::vector<std::reference_wrapper<Renderer>>> m_renderers;

            EventDispatcher &m_eventDispatcher;
            std::unordered_map<EventDispatcher::EventID, std::string> m_subscriptions;

    };
}