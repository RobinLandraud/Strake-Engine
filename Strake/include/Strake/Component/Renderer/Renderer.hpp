#pragma once

#include <Strake/Component/Component.hpp>
#include <Strake/Component/Camera.hpp>
#include <Strake/Dispatcher/EventDispatcher.hpp>
#include <Strake/Dispatcher/EventData.hpp>

namespace Strake {
    enum class RendererType {
        None,
        MeshRenderer,
        WireFrameRenderer,
        UI
    };

    class Renderer : public Component
    {
        public:
            Renderer(GameObject &parent, RendererType type);
            ~Renderer();

            virtual void preRender();
            virtual void render(Camera &camera);
            virtual void postRender();

            [[nodiscard]] RendererType getType() const;
            void updateLayer(int oldLayer);

        protected:
            RendererType m_type;
    };
}