#pragma once

#include <vector>
#include <functional>
#include <Strake/Component/MeshRenderer.hpp>

namespace Strake {
    class RendererManager {
        public:
            explicit RendererManager(EventDispatcher &eventDispatcher);
            ~RendererManager();
            RendererManager(const RendererManager &other) = delete;
            RendererManager(RendererManager &&other) = delete;
            RendererManager &operator=(const RendererManager &other) = delete;
            RendererManager &operator=(RendererManager &&other) = delete;

            void addRenderer(MeshRenderer &renderer);
            void removeRenderer(MeshRenderer &renderer);
            void clear();
            [[nodiscard]] std::vector<std::reference_wrapper<MeshRenderer>> &getRenderers();

        private:
            std::vector<std::reference_wrapper<MeshRenderer>> m_renderers;

            EventDispatcher &m_eventDispatcher;
            std::unordered_map<EventDispatcher::EventID, std::string> m_subscriptions;

    };
}