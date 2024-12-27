#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <ECS/Lights.hpp>

namespace ECS {

    ///////////////////////////////
    /// ShadowMap
    ///////////////////////////////

    ShadowMap::ShadowMap() :
        m_size(1024, 1024)
    {
        glGenFramebuffers(1, &m_shadowFBO);
        glGenTextures(1, &m_shadowMap);
        glBindTexture(GL_TEXTURE_2D, m_shadowMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_size.x, m_size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        m_lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 20.0f);
    }

    ShadowMap::~ShadowMap() {
        glDeleteFramebuffers(1, &m_shadowFBO);
        glDeleteTextures(1, &m_shadowMap);
    }

    GLuint ShadowMap::getShadowMap() const {
        return m_shadowMap;
    }

    GLuint ShadowMap::getShadowFBO() const {
        return m_shadowFBO;
    }

    const glm::mat4 &ShadowMap::getLightProjection() const {
        return m_lightProjection;
    }

    glm::vec2 ShadowMap::getSize() const {
        return m_size;
    }

    void ShadowMap::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFBO);
        glViewport(0, 0, m_size.x, m_size.y);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void ShadowMap::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void ShadowMap::addObject(GameObject &object) {
        m_objects.push_back(object);
    }

    const std::vector<std::reference_wrapper<GameObject>> &ShadowMap::getObjects() const {
        return m_objects;
    }

    void ShadowMap::clearObjects() {
        m_objects.clear();
    }

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

    void Light::update() {
        m_shadowMap.clearObjects();
    }

    ShadowMap &Light::getShadowMap() {
        return m_shadowMap;
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