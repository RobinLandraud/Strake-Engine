#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <Strake/Component/Light/Light.hpp>
#include <Strake/Component/Renderer/MeshRenderer.hpp>

namespace Strake {
    Light::Light(GameObject &parent, LightType type) :
        Component(parent),
        m_type(std::move(type)),
        m_color(1.0f), // white
        m_intensity(1.0f), // full intensity
        m_minIntensity(0.0f) // no minimum intensity
    {
        setDerivedType(typeid(Light)); // a game object cannot have several lights
        EventData<Light> eventData(*this, "addLight");
        parent.getEventDispatcher().broadcast(eventData);
    }

    Light::~Light() {
        EventData<Light> eventData(*this, "removeLight");
        getParent().getEventDispatcher().broadcast(eventData);
    }

    void Light::setColor(const glm::vec3 &color) {
        m_color = color;
    }

    void Light::setIntensity(float intensity) {
        m_intensity = intensity;
    }

    void Light::setMinIntensity(float minIntensity) {
        m_minIntensity = minIntensity;
    }

    float Light::getIntensity() const {
        return m_intensity;
    }

    float Light::getMinIntensity() const {
        return m_minIntensity;
    }

    const glm::vec3 &Light::getColor() const {
        return m_color;
    }

    LightType Light::getType() const {
        return m_type;
    }

    ShadowMap &Light::getShadowMap() {
        return m_shadowMap;
    }

    void Light::renderShadowMap(ShaderProgram &shaderProgram) {} // default implementation

    const ShadowMap &Light::getShadowMap() const {
        return m_shadowMap;
    }

    void Light::updateLayer(int oldLayer) {
        std::pair<int, Light &> pair = {oldLayer, *this};
        EventData<std::pair<int, Light &>> eventData(pair, "moveLight");
        EventDispatcher &dispatcher = getParent().getEventDispatcher();
        dispatcher.broadcast(eventData);
    }
}