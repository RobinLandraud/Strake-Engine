#include <ECS/Transform.hpp>

namespace ECS {
    Transform::Transform(GameObject &parent) : Component(parent) {
        setDerivedType(typeid(Transform));
    }

    const glm::mat4 &Transform::getWorldMatrix() {
        if (m_worldDirty == true) {
            updateWorldMatrix();
        }
        return m_worldMatrix;
    }

    const glm::mat4 &Transform::getLocalMatrix() {
        if (m_localDirty == true) {
            updateLocalMatrix();
        }
        return m_localMatrix;
    }

    void Transform::setWorldDirty() {
        m_worldDirty = true;
        for (auto &child : getParent().getChildren()) {
            child.second->getTransform().setWorldDirty();
        }
    }

    /////////////////////////////////////////////////////
    /// Local Space
    /////////////////////////////////////////////////////

    const glm::vec3 &Transform::getLocalPosition() const {
        return m_localPosition;
    }

    const glm::vec3 &Transform::getLocalRotation() const {
        return m_localRotation;
    }

    const glm::vec3 &Transform::getLocalFront() const {
        return m_localFront;
    }

    const glm::vec3 &Transform::getLocalUp() const {
        return m_localUp;
    }

    const glm::vec3 &Transform::getLocalRight() const {
        return m_localRight;
    }

    const glm::vec3 &Transform::getLocalScale() const {
        return m_localScale;
    }

    void Transform::setLocalPosition(const glm::vec3 &position) {
        m_localPosition = position;
        m_localDirty = true;
        setWorldDirty();
    }

    void Transform::translateLocal(const glm::vec3 &translation) {
        m_localPosition += translation.x * m_localRight;
        m_localPosition += translation.y * m_localUp;
        m_localPosition += translation.z * m_localFront;
        m_localDirty = true;
        setWorldDirty();
    }

    void Transform::setLocalRotation(const glm::vec3 &rotation) {
        m_localRotation = rotation;
        m_localDirty = true;
        setWorldDirty();
        updateEulerAngles();
    }

    void Transform::rotateLocal(const glm::vec3 &rotation) {
        m_localRotation += rotation;
        m_localDirty = true;
        setWorldDirty();
        updateEulerAngles();
    }

    void Transform::setLocalRoll(float roll) {
        m_localRotation.x = roll;
        m_localDirty = true;
        setWorldDirty();
        updateEulerAngles();
    }

    void Transform::setLocalPitch(float pitch) {
        m_localRotation.y = pitch;
        m_localDirty = true;
        setWorldDirty();
        updateEulerAngles();
    }

    void Transform::setLocalYaw(float yaw) {
        m_localRotation.z = yaw;
        m_localDirty = true;
        setWorldDirty();
        updateEulerAngles();
    }

    void Transform::setLocalScale(const glm::vec3 &scale) {
        m_localScale = scale;
        m_localDirty = true;
        setWorldDirty();
    }

    void Transform::scaleLocal(const glm::vec3 &scale) {
        m_localScale *= scale;
        m_localDirty = true;
        setWorldDirty();
    }

    void Transform::updateLocalMatrix() {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_localPosition);
        glm::mat4 rotationMatrixX = glm::rotate(glm::mat4(1.0f), glm::radians(m_localRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotationMatrixY = glm::rotate(glm::mat4(1.0f), glm::radians(m_localRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotationMatrixZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_localRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotationMatrix = rotationMatrixZ * rotationMatrixY * rotationMatrixX;
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_localScale);
        m_localMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    }

    /////////////////////////////////////////////////////
    /// World Space
    /////////////////////////////////////////////////////

    void Transform::rotate(const glm::vec3 &rotation) {
        // do after
    }

    void Transform::updateWorldMatrix() {
        GameObject &parent = getParent();
        if (parent.hasParent() == false) {
            m_worldMatrix = getLocalMatrix();
        } else {
            m_worldMatrix = parent.getParent().getTransform().getWorldMatrix() * getLocalMatrix();
        }
        m_worldDirty = false;
    }

    void Transform::updateEulerAngles() {
        // local 
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_localRotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * // Yaw
                                   glm::rotate(glm::mat4(1.0f), glm::radians(m_localRotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * // Pitch
                                   glm::rotate(glm::mat4(1.0f), glm::radians(m_localRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));  // Roll
        m_localFront = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)));
        m_localRight = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
        m_localUp = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    }
}