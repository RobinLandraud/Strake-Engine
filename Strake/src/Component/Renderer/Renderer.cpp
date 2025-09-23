#include <Strake/Component/Renderer/Renderer.hpp>

namespace Strake {
    Renderer::Renderer(GameObject &parent, RendererType type) :
        Component(parent),
        m_type(type)
    {
        setDerivedType(typeid(Renderer));
        EventData<Renderer> eventData(*this, "addRenderer");
        parent.getEventDispatcher().broadcast(eventData);
    }

    Renderer::~Renderer()
    {
        EventData<Renderer> eventData(*this, "removeRenderer");
        getParent().getEventDispatcher().broadcast(eventData);
    }

    void Renderer::preRender()
    {
    }

    void Renderer::render(Camera &camera)
    {
    }

    void Renderer::postRender()
    {
    }

    RendererType Renderer::getType() const
    {
        return m_type;
    }

    void Renderer::updateLayer(int oldLayer)
    {
        std::pair<int, Renderer &> pair = {oldLayer, *this};
        EventData<std::pair<int, Renderer &>> eventData(pair, "moveRenderer");
        getParent().getEventDispatcher().broadcast(eventData);
    }
}