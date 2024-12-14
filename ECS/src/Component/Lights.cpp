#include <ECS/Lights.hpp>

namespace ECS {

    ///////////////////////////////
    /// Light
    ///////////////////////////////

    Light::Light(GameObject &parent, LightType type) :
        Component(parent),
        m_type(std::move(type)),
        m_color(1.0f), // white
        m_intensity(1.0f) // full intensity
    {
        setDerivedType(typeid(Light)); // a game object cannot have several lights
    }

    void Light::setColor(const glm::vec3 &color) {
        m_color = color;
    }

    void Light::setIntensity(float intensity) {
        m_intensity = intensity;
    }

    float Light::getIntensity() const {
        return m_intensity;
    }

    const glm::vec3 &Light::getColor() const {
        return m_color;
    }

    ///////////////////////////////
    /// PointLight
    ///////////////////////////////

    PointLight::PointLight(GameObject &parent) :
        Light(parent, LightType::Point),
        m_constant(1.0f),
        m_linear(0.09f),
        m_quadratic(0.032f),
        r_transform(parent.getTransform())
    {
    }

    void PointLight::setPosition(const glm::vec3 &position) {
        r_transform.setLocalPosition(position);
    }

    void PointLight::setConstant(float constant) {
        m_constant = constant;
    }

    void PointLight::setLinear(float linear) {
        m_linear = linear;
    }

    void PointLight::setQuadratic(float quadratic) {
        m_quadratic = quadratic;
    }

    const glm::vec3 &PointLight::getPosition() const {
        return r_transform.getLocalPosition();
    }

    float PointLight::getConstant() const {
        return m_constant;
    }

    float PointLight::getLinear() const {
        return m_linear;
    }

    float PointLight::getQuadratic() const {
        return m_quadratic;
    }
}