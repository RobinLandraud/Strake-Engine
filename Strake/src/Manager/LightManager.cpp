#include <Strake/Manager/LightManager.hpp>

namespace Strake {
    LightManager::LightManager(EventDispatcher &eventDispatcher) :
        m_shadowShaderProgram(
            std::string(RESOURCES_PATH) + "/Shaders/shadow/vertex.glsl",
            std::string(RESOURCES_PATH) + "/Shaders/shadow/fragment.glsl"),
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

    void LightManager::clearObjects()
    {
        for (auto &light : m_lights) {
            light.get().getShadowMap().clearObjects();
        }
    }

    void LightManager::renderShadowMaps(int winWidth, int winHeight)
    {
        glViewport(0, 0, 4096, 4096);
        m_shadowShaderProgram.use();
        for (auto &light : m_lights) {
            light.get().renderShadowMap(m_shadowShaderProgram);
        }
        glViewport(0, 0, winWidth, winHeight);
    }
}