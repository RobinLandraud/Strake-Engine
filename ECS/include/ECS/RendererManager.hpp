#include <vector>
#include <functional>
#include <ECS/MeshRenderer.hpp>

namespace ECS {
    class RendererManager {
        public:
            explicit RendererManager(EventDispatcher &eventDispatcher);
            ~RendererManager() = default;
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
    };
}