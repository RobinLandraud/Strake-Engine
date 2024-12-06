#include <ECS/Camera.hpp>

namespace ECS {
    Camera::Camera(GameObject &parent) : Component(parent)
    {
        setDerivedType(typeid(Camera));
    }

    void Camera::lateUpdate()
    {
        if (m_viewNeedUpdate) {
            updateViewMatrix();
            m_viewNeedUpdate = false;
            m_hasChangedView = true;
        }
        if (m_projectionNeedUpdate) {
            updateProjectionMatrix();
            m_projectionNeedUpdate = false;
            m_hasChangedProjection = true;
        }
    }

    void Camera::setProjection(float fov, float aspect, float near, float far)
    {
        m_fov = fov;
        m_aspect = aspect;
        m_near = near;
        m_far = far;
        m_projectionNeedUpdate = true;
    }

    void Camera::setPosition(const glm::vec3 &position)
    {
        m_position = position;
        m_viewNeedUpdate = true;
    }

    void Camera::setFront(const glm::vec3 &front)
    {
        m_front = front;
        m_viewNeedUpdate = true;
    }

    void Camera::setUp(const glm::vec3 &up)
    {
        m_up = up;
        m_viewNeedUpdate = true;
    }

    void Camera::setRoll(float roll)
    {
        m_roll = roll;
        m_viewNeedUpdate = true;
    }

    void Camera::setPitch(float pitch)
    {
        m_pitch = pitch;
        m_viewNeedUpdate = true;
    }

    void Camera::setYaw(float yaw)
    {
        m_yaw = yaw;
        m_viewNeedUpdate = true;
    }

    void Camera::translate(const glm::vec3 &translation)
    {
        // Calculate the right vector from the front and up vectors
        glm::vec3 right = glm::normalize(glm::cross(m_front, m_up));

        // Translate the position based on the camera's orientation
        m_position += translation.x * right;       // Move along the right vector
        m_position += translation.y * m_up;        // Move along the up vector
        m_position += translation.z * m_front;     // Move along the front vector

        m_viewNeedUpdate = true;
    }

    void Camera::rotate(float roll, float pitch, float yaw)
    {
        m_roll += roll;
        m_pitch += pitch;
        m_yaw += yaw;
        m_viewNeedUpdate = true;
    }

    void Camera::rotate(const glm::vec3 &rotation)
    {
        m_roll += rotation.x;
        m_pitch += rotation.y;
        m_yaw += rotation.z;
        m_viewNeedUpdate = true;
    }

    void Camera::setFov(float fov)
    {
        m_fov = fov;
        m_projectionNeedUpdate = true;
    }

    void Camera::setAspect(float aspect)
    {
        m_aspect = aspect;
        m_projectionNeedUpdate = true;
    }

    void Camera::setNear(float near)
    {
        m_near = near;
        m_projectionNeedUpdate = true;
    }

    void Camera::setFar(float far)
    {
        m_far = far;
        m_projectionNeedUpdate = true;
    }

    const glm::mat4 &Camera::getViewMatrix() const
    {
        return m_viewMatrix;
    }

    const glm::mat4 &Camera::getProjectionMatrix() const
    {
        return m_projectionMatrix;
    }

    const glm::vec3 &Camera::getPosition() const
    {
        return m_position;
    }

    const glm::vec3 &Camera::getFront() const
    {
        return m_front;
    }

    const glm::vec3 &Camera::getUp() const
    {
        return m_up;
    }

    float Camera::getRoll() const
    {
        return m_roll;
    }

    float Camera::getPitch() const
    {
        return m_pitch;
    }

    float Camera::getYaw() const
    {
        return m_yaw;
    }

    float Camera::getFov() const
    {
        return m_fov;
    }

    float Camera::getAspect() const
    {
        return m_aspect;
    }

    float Camera::getNear() const
    {
        return m_near;
    }

    float Camera::getFar() const
    {
        return m_far;
    }

    void Camera::updateViewMatrix()
    {
        m_front = glm::normalize(glm::vec3(
            cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw)),
            sin(glm::radians(m_pitch)),
            cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw))
        ));
        m_up = glm::normalize(glm::cross(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)), m_front));
        m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
    }

    void Camera::updateProjectionMatrix()
    {
        m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
    }

    void Camera::resetUpdateFlags()
    {
        m_hasChangedView = false;
        m_hasChangedProjection = false;
    }

    bool Camera::hasChangedView() const
    {
        return m_hasChangedView;
    }

    bool Camera::hasChangedProjection() const
    {
        return m_hasChangedProjection;
    }
}