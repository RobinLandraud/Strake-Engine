#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <ECS/Lights.hpp>

namespace ECS {

    ///////////////////////////////
    /// Light
    ///////////////////////////////

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

    ///////////////////////////////
    /// PointLight
    ///////////////////////////////

    PointLight::PointLight(GameObject &parent) :
        Light(parent, LightType::Point),
        r_transform(parent.getTransform())
    {
    }

    void PointLight::setPosition(const glm::vec3 &position) {
        r_transform.setLocalPosition(position);
    }

    const glm::vec3 PointLight::getPosition() const {
        return r_transform.getWorldPosition();
    }

    ///////////////////////////////
    /// DirectionalLight
    ///////////////////////////////

    DirectionalLight::DirectionalLight(GameObject &parent) :
        Light(parent, LightType::Directional),
        r_transform(parent.getTransform())
    {
    }

    void DirectionalLight::setRotation(const glm::vec3 &rotation) {
        // set the rotation in local space
        r_transform.setLocalRotation(rotation);
    }

    void DirectionalLight::setDirection(const glm::vec3 &direction) {
        r_transform.setLocalPitch(glm::degrees(asin(direction.y)));
        r_transform.setLocalYaw(glm::degrees(atan2(direction.x, direction.z)));
    }

    glm::vec3 DirectionalLight::getDirection() const {
        const glm::mat4 &mat = r_transform.getWorldMatrix();
        return glm::normalize(-glm::vec3( // mustn be transform class value (only updated if needed)
            mat[1][0], mat[1][1], mat[1][2]
        ));
    }
}