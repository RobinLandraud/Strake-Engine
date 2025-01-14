#include <Strake/Manager/RendererManager.hpp>

namespace Strake {
    RendererManager::RendererManager(EventDispatcher &eventDispatcher) :
        m_eventDispatcher(eventDispatcher)
    {
        m_subscriptions[m_eventDispatcher.subscribe("addRenderer", [this](const Event &event) {
            MeshRenderer &renderer = static_cast<const EventData<MeshRenderer> &>(event).getValue();
            addRenderer(renderer);
        })] = "addRenderer";

        m_subscriptions[m_eventDispatcher.subscribe("removeRenderer", [this](const Event &event) {
            MeshRenderer &renderer = static_cast<const EventData<MeshRenderer> &>(event).getValue();
            removeRenderer(renderer);
        })] = "removeRenderer";

        m_subscriptions[m_eventDispatcher.subscribe("clearRenderers", [this](const Event &event) {
            clear();
        })] = "clearRenderers";
    }

    RendererManager::~RendererManager()
    {
        for (const auto &[id, event] : m_subscriptions) {
            m_eventDispatcher.unsubscribe(event, id);
        }
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