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
        
        m_subscriptions[m_eventDispatcher.subscribe("moveRenderer", [this](const Event &event) {
            std::pair<int, Renderer &> data = static_cast<const EventData<std::pair<int, Renderer &>> &>(event).getValue();
            moveRenderer(data.second, data.first);
        })] = "moveRenderer";
    }

    RendererManager::~RendererManager()
    {
        for (const auto &[id, event] : m_subscriptions) {
            m_eventDispatcher.unsubscribe(event, id);
        }
    }

    void RendererManager::addRenderer(Renderer &renderer)
    {
        m_renderers[renderer.getParent().getLayer().getPriority()].push_back(renderer);
    }

    void RendererManager::removeRenderer(Renderer &renderer)
    {
        int layer = renderer.getParent().getLayer().getPriority();
        auto it = std::find_if(m_renderers[layer].begin(), m_renderers[layer].end(),
            [&renderer](Renderer &r) {
                return &r == &renderer;
            }
        );
        if (it != m_renderers[layer].end()) {
            m_renderers[layer].erase(it);
        }
    }

    void RendererManager::moveRenderer(Renderer &renderer, int oldLayer)
    {
        int newLayer = renderer.getParent().getLayer().getPriority();
        auto it = std::find_if(m_renderers[oldLayer].begin(), m_renderers[oldLayer].end(),
            [&renderer](Renderer &r) {
                return &r == &renderer;
            }
        );
        if (it != m_renderers[oldLayer].end()) {
            m_renderers[oldLayer].erase(it);
            m_renderers[newLayer].push_back(renderer);
        }
    }

    void RendererManager::clear()
    {
        m_renderers.clear();
    }

    void RendererManager::clearDepth() const {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    std::vector<std::reference_wrapper<Renderer>> &RendererManager::getRenderers(int layer)
    {
        return m_renderers[layer];
    }

    std::map<int, std::vector<std::reference_wrapper<Renderer>>> &RendererManager::getRenderers()
    {
        return m_renderers;
    }

    std::vector<std::reference_wrapper<Renderer>> RendererManager::updateLightings(int layer, std::vector<std::reference_wrapper<Light>> &lights)
    {
        std::vector<std::reference_wrapper<Renderer>> in_frustrum_renderers;
        for (auto &renderer : m_renderers[layer]) {
            in_frustrum_renderers.push_back(renderer);
        }
        for (auto &renderer : in_frustrum_renderers) {
            if (renderer.get().getType() == RendererType::MeshRenderer)
            {
                MeshRenderer &meshRenderer = static_cast<MeshRenderer &>(renderer.get());
                meshRenderer.updateLights(lights);
            }
        }
        return in_frustrum_renderers;
    }
}