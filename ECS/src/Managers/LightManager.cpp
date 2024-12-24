#include <ECS/LightManager.hpp>

namespace ECS {
    LightManager::LightManager(EventDispatcher &eventDispatcher) :
        m_eventDispatcher(eventDispatcher)
    {
        m_eventDispatcher.subscribe("addLight", [this](const Event &event) {
            const Light &light = static_cast<const EventData<Light> &>(event).getValue();
            addLight(light);
        });

        m_eventDispatcher.subscribe("removeLight", [this](const Event &event) {
            const Light &light = static_cast<const EventData<Light> &>(event).getValue();
            removeLight(light);
        });

        m_eventDispatcher.subscribe("clearLights", [this](const Event &event) {
            clear();
        });

        m_eventDispatcher.subscribe("updateRendererLights", [this](const Event &event) {
            const MeshRenderer &renderer = static_cast<const EventData<MeshRenderer> &>(event).getValue();
            ShaderProgram &program = renderer.getMaterial().getShaderProgram();
            if (getLights().empty()) {
                return;
            }
            const PointLight &light = static_cast<const PointLight &>(getLights().front().get());
            program.setUniform("light.position", light.getPosition());
            program.setUniform("light.color", light.getColor());
            program.setUniform("light.intensity", light.getIntensity());
        });
    }

    void LightManager::addLight(const Light &light)
    {
        m_lights.push_back(light);
    }

    void LightManager::removeLight(const Light &light)
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

    std::vector<std::reference_wrapper<const Light>> &LightManager::getLights()
    {
        return m_lights;
    }
}