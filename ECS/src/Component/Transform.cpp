#include <ECS/Transform.hpp>

namespace ECS {
    void Transform::lateUpdate() {
        if (needUpdate) {
            updateMatrix();
            needUpdate = false;
        }
    }

    void Transform::updateMatrix() {
        m_matrix = glm::mat4(1.0f);
        m_matrix = glm::translate(m_matrix, m_position);
        m_matrix = glm::rotate(m_matrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_matrix = glm::rotate(m_matrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        m_matrix = glm::rotate(m_matrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_matrix = glm::scale(m_matrix, m_scale);
    }

    void Transform::setPosition(const glm::vec3 &position) {
        m_position = position;
        needUpdate = true;
    }

    void Transform::setRotation(const glm::vec3 &rotation) {
        m_rotation = rotation;
        needUpdate = true;
    }

    void Transform::setScale(const glm::vec3 &scale) {
        m_scale = scale;
        needUpdate = true;
    }

    void Transform::translate(const glm::vec3 &translation) {
        m_position += translation;
        needUpdate = true;
    }

    void Transform::rotate(const glm::vec3 &rotation) {
        m_rotation += rotation;
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

    const glm::vec3 &Transform::getScale() const {
        return m_scale;
    }
}