#include <Strake/Manager/LightManager.hpp>

namespace Strake {
    LightManager::LightManager(EventDispatcher &eventDispatcher) :
        m_eventDispatcher(eventDispatcher)
    {
        m_subscriptions[m_eventDispatcher.subscribe("addLight", [this](const Event &event) {
            Light &light = static_cast<const EventData<Light> &>(event).getValue();
            addLight(light);
        })] = "addLight";

        m_subscriptions[m_eventDispatcher.subscribe("removeLight", [this](const Event &event) {
            Light &light = static_cast<const EventData<Light> &>(event).getValue();
            removeLight(light);
        })] = "removeLight";

        m_subscriptions[m_eventDispatcher.subscribe("clearLights", [this](const Event &event) {
            clear();
        })] = "clearLights";
    }

    LightManager::~LightManager()
    {
        for (const auto &[id, event] : m_subscriptions) {
            m_eventDispatcher.unsubscribe(event, id);
        }
    }

    void LightManager::addLight(Light &light)
    {
        m_lights.push_back(light);
    }

    void LightManager::removeLight(Light &light)
    {
        auto it = std::find_if(m_lights.begin(), m_lights.end(),
            [&light](const std::reference_wrapper<const Light>& ref) {
                return &ref.get() == &light;
            }
        );
        if (it != m_lights.end()) {
            m_lights.erase(it);
        }
    }

    void LightManager::clear()
    {
        m_lights.clear();
    }

    std::vector<std::reference_wrapper<Light>> &LightManager::getLights()
    {
        return m_lights;
    }
}