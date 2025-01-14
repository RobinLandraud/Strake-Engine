#include <Strake/Manager/RendererManager.hpp>

namespace Strake {
    RendererManager::RendererManager(EventDispatcher &eventDispatcher) :
        m_eventDispatcher(eventDispatcher)
    {
        m_subscriptions[m_eventDispatcher.subscribe("addRenderer", [this](const Event &event) {
            Renderer &renderer = static_cast<const EventData<Renderer> &>(event).getValue();
            addRenderer(renderer);
        })] = "addRenderer";

        m_subscriptions[m_eventDispatcher.subscribe("removeRenderer", [this](const Event &event) {
            Renderer &renderer = static_cast<const EventData<Renderer> &>(event).getValue();
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

    void RendererManager::addRenderer(Renderer &renderer)
    {
        m_renderers.push_back(renderer);
    }

    void RendererManager::removeRenderer(Renderer &renderer)
    {
        auto it = std::find_if(m_renderers.begin(), m_renderers.end(), [&renderer](const Renderer &r) {
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

    std::vector<std::reference_wrapper<Renderer>> &RendererManager::getRenderers()
    {
        return m_renderers;
    }
}