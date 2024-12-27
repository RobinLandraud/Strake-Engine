#include <ECS/LightManager.hpp>

namespace ECS {
    LightManager::LightManager(EventDispatcher &eventDispatcher) :
        m_eventDispatcher(eventDispatcher)
    {
        m_eventDispatcher.subscribe("addLight", [this](const Event &event) {
            Light &light = static_cast<const EventData<Light> &>(event).getValue();
            addLight(light);
        });

        m_eventDispatcher.subscribe("removeLight", [this](const Event &event) {
            Light &light = static_cast<const EventData<Light> &>(event).getValue();
            removeLight(light);
        });

        m_eventDispatcher.subscribe("clearLights", [this](const Event &event) {
            clear();
        });

        m_eventDispatcher.subscribe("updateRendererLights", [this](const Event &event) {
            MeshRenderer &renderer = static_cast<const EventData<MeshRenderer> &>(event).getValue();
            if (getLights().empty()) {
                return;
            }
            int numLights = std::min(static_cast<int>(getLights().size()), 8);
            for (int i = 0; i < numLights; ++i) {
                Light &light = getLights()[i].get();
                renderer.addLight(light);
                light.getShadowMap().addObject(renderer.getParent());
            }
        });

        m_eventDispatcher.subscribe("applyRendererLights", [this](const Event &event) {
            MeshRenderer &renderer = static_cast<const EventData<MeshRenderer> &>(event).getValue();
            ShaderProgram &program = renderer.getMaterial().getShaderProgram();
            if (getLights().empty()) {
                return;
            }
            std::vector<std::reference_wrapper<const Light>> &lights = renderer.getLights();
            int numLights = std::min(static_cast<int>(lights.size()), 8);
            program.setUniform("numLights", numLights);

            for (int i = 0; i < numLights; ++i) {
                const Light &light = lights[i].get();

                program.setUniform("lights[" + std::to_string(i) + "].type", static_cast<int>(light.getType()));
                program.setUniform("lights[" + std::to_string(i) + "].color", light.getColor());
                program.setUniform("lights[" + std::to_string(i) + "].intensity", light.getIntensity());
                program.setUniform("lights[" + std::to_string(i) + "].ambient", light.getMinIntensity());

                switch (light.getType()) {
                    case LightType::Point: {
                        const PointLight &pointLight = static_cast<const PointLight &>(light);
                        program.setUniform("lights[" + std::to_string(i) + "].position", pointLight.getPosition());
                        break;
                    }
                    case LightType::Directional: {
                        const DirectionalLight &directionalLight = static_cast<const DirectionalLight &>(light);
                        program.setUniform("lights[" + std::to_string(i) + "].direction", directionalLight.getDirection());
                        break;
                    }
                    case LightType::Spot: {
                        // TODO
                        break;
                    }
                }
            }

            renderer.clearLights();
        });
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