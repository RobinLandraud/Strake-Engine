#include <ECS/Transform.hpp>

namespace ECS {
    Transform::Transform(GameObject &parent) : Component(parent) {
        setDerivedType(typeid(Transform));
    }

    void Transform::lateUpdate() {
        if (needUpdate) {
            updateMatrix();
            needUpdate = false;
        }
    }

    void Transform::updateEulerAngles() {
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) * // Yaw
                                   glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) * // Pitch
                                   glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));  // Roll
        m_front = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)));
        m_right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
        m_up = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
    }

    void Transform::updateMatrix() {
        m_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
        m_matrix = glm::scale(m_matrix, m_scale);
    }

    void Transform::setPosition(const glm::vec3 &position) {
        m_position = position;
        needUpdate = true;
    }

    void Transform::setRotation(const glm::vec3 &rotation) {
        m_rotation = rotation;
        updateEulerAngles();
        needUpdate = true;
    }

    void Transform::setRoll(float roll) {
        m_rotation.x = roll;
        updateEulerAngles();
        needUpdate = true;
    }

    void Transform::setPitch(float pitch) {
        m_rotation.y = pitch;
        updateEulerAngles();
        needUpdate = true;
    }

    void Transform::setYaw(float yaw) {
        m_rotation.z = yaw;
        updateEulerAngles();
        needUpdate = true;
    }

    void Transform::setScale(const glm::vec3 &scale) {
        m_scale = scale;
        needUpdate = true;
    }

    void Transform::translate(const glm::vec3 &translation) {
        m_position += translation.x * m_right;
        m_position += translation.y * m_up;
        m_position += translation.z * m_front;
        needUpdate = true;
    }

    void Transform::rotate(const glm::vec3 &rotation) {
        m_rotation += rotation;
        updateEulerAngles();
        needUpdate = true;
    }

    void Transform::scale(const glm::vec3 &scaleFactor) {
        m_scale *= scaleFactor;
        needUpdate = true;
    }

    const glm::mat4 &Transform::getMatrix() {
        return m_matrix;
    }

    const glm::vec3 &Transform::getPosition() const {
        return m_position;
    }

    const glm::vec3 &Transform::getRotation() const {
        return m_rotation;
    }

    const glm::vec3 &Transform::getFront() const {
        return m_front;
    }

    const glm::vec3 &Transform::getUp() const {
        return m_up;
    }

    const glm::vec3 &Transform::getRight() const {
        return m_right;
    }

    const glm::vec3 &Transform::getScale() const {
        return m_scale;
    }
}