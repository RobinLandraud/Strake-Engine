#include <ECS/RendererManager.hpp>

namespace ECS {
    RendererManager::RendererManager(EventDispatcher &eventDispatcher) :
        m_eventDispatcher(eventDispatcher)
    {
        m_eventDispatcher.subscribe("addRenderer", [this](const Event &event) {
            MeshRenderer &renderer = static_cast<const EventData<MeshRenderer> &>(event).getValue();
            addRenderer(renderer);
        });

        m_eventDispatcher.subscribe("removeRenderer", [this](const Event &event) {
            MeshRenderer &renderer = static_cast<const EventData<MeshRenderer> &>(event).getValue();
            removeRenderer(renderer);
        });

        m_eventDispatcher.subscribe("clearRenderers", [this](const Event &event) {
            clear();
        });
    }

    void RendererManager::addRenderer(MeshRenderer &renderer)
    {
        m_renderers.push_back(renderer);
    }

    void RendererManager::removeRenderer(MeshRenderer &renderer)
    {
        auto it = std::find_if(m_renderers.begin(), m_renderers.end(), [&renderer](const MeshRenderer &r) {
            return &r == &renderer;
        });

        if (it != m_renderers.end()) {
            m_renderers.erase(it);
        }
    }

    void RendererManager::clear()
    {
        m_renderers.clear();
    }

    std::vector<std::reference_wrapper<MeshRenderer>> &RendererManager::getRenderers()
    {
        return m_renderers;
    }
}