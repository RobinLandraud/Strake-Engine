#include <Strake/Manager/LightManager.hpp>

namespace Strake {
    LightManager::LightManager(EventDispatcher &eventDispatcher) :
        m_shadowShaderProgram(
            std::string(RESOURCES_PATH) + "/Shaders/shadow/vertex.glsl",
            std::string(RESOURCES_PATH) + "/Shaders/shadow/fragment.glsl"),
        m_eventDispatcher(eventDispatcher)
    {
        m_subscriptions[m_eventDispatcher.subscribe("addLight", [this](const Event &event) {
            std::pair<Light &, int> &data = static_cast<const EventData<std::pair<Light &, int>> &>(event).getValue();
            addLight(data.first, data.second);
        })] = "addLight";

        m_subscriptions[m_eventDispatcher.subscribe("removeLight", [this](const Event &event) {
            std::pair<Light &, int> &data = static_cast<const EventData<std::pair<Light &, int>> &>(event).getValue();
            removeLight(data.first, data.second);
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

    void LightManager::addLight(Light &light, int layer)
    {
        auto it = std::find_if(m_lights[layer].begin(), m_lights[layer].end(),
            [&light](const std::reference_wrapper<const Light>& ref) {
                return &ref.get() == &light;
            }
        );
        if (it == m_lights[layer].end()) {
            m_lights[layer].push_back(light);
        }
    }

    void LightManager::removeLight(Light &light, int layer)
    {
        auto it = std::find_if(m_lights[layer].begin(), m_lights[layer].end(),
            [&light](const std::reference_wrapper<const Light>& ref) {
                return &ref.get() == &light;
            }
        );
        if (it != m_lights[layer].end()) {
            m_lights[layer].erase(it);
        }
    }

    void LightManager::clear()
    {
        m_lights.clear();
    }

    std::vector<std::reference_wrapper<Light>> &LightManager::getLights(int layer)
    {
        return m_lights[layer];
    }

    void LightManager::clearObjects(int layer)
    {
        for (auto &light : m_lights[layer]) {
            light.get().getShadowMap().clearObjects();
        }
    }

    void LightManager::renderShadowMaps(int layer, int winWidth, int winHeight)
    {
        glViewport(0, 0, 4096, 4096);
        m_shadowShaderProgram.use();
        for (auto &light : m_lights[layer]) {
            light.get().renderShadowMap(m_shadowShaderProgram);
        }
        glViewport(0, 0, winWidth, winHeight);
    }
}