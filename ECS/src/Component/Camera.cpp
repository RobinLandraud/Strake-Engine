#include <ECS/Camera.hpp>
#include <ECS/Transform.hpp>

namespace ECS {
    Camera::Camera(GameObject &parent) :
        Component(parent),
        m_transform(parent.getComponent<Transform>())
    {
        setDerivedType(typeid(Camera));
    }

    void Camera::lateUpdate()
    {
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

    //void Camera::setPosition(const glm::vec3 &position)
    //{
    //    m_transform.setPosition(position);
    //}
//
    //void Camera::setFront(const glm::vec3 &front)
    //{
    //    m_transform.setRotation(glm::vec3(
    //        glm::degrees(asin(front.y)),
    //        glm::degrees(atan2(front.x, front.z)),
    //        0.0f
    //    ));
    //}

    //void Camera::setUp(const glm::vec3 &up)
    //{
    //    //m_transform.setLocalRotation(glm::vec3(
    //    //    glm::degrees(asin(m_transform.getFront().y)),
    //    //    glm::degrees(atan2(m_transform.getFront().x, m_transform.getFront().z)),
    //    //    glm::degrees(atan2(up.x, up.z))
    //    //));
    //}

    //void Camera::setRight(const glm::vec3 &right)
    //{
    //    //m_transform.setRotation(glm::vec3(
    //    //    glm::degrees(asin(m_transform.getFront().y)),
    //    //    glm::degrees(atan2(m_transform.getFront().x, m_transform.getFront().z)),
    //    //    glm::degrees(atan2(m_transform.getUp().x, m_transform.getUp().z))
    //    //));
    //}
//
    //void Camera::setRoll(float roll)
    //{
    //    m_transform.setRoll(roll);
    //}
//
    //void Camera::setPitch(float pitch)
    //{
    //    m_transform.setPitch(pitch);
    //}
//
    //void Camera::setYaw(float yaw)
    //{
    //    m_transform.setYaw(yaw);
    //}
//
    //void Camera::translate(const glm::vec3 &translation)
    //{
    //    m_transform.translate(translation);
    //}
//
    //void Camera::rotate(float roll, float pitch, float yaw)
    //{
    //    m_transform.rotate(glm::vec3(roll, pitch, yaw));
    //}
//
    //void Camera::rotate(const glm::vec3 &rotation)
    //{
    //    m_transform.rotate(rotation);
    //}

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

    const glm::mat4 &Camera::getViewMatrix()
    {
        glm::mat4 worldMatrix = m_transform.getWorldMatrix();
        m_viewMatrix = glm::inverse(worldMatrix);
        return m_viewMatrix;
    }

    const glm::mat4 &Camera::getProjectionMatrix() const
    {
        return m_projectionMatrix;
    }

    const glm::vec3 &Camera::getPosition() const
    {
        return m_transform.getLocalPosition();
    }

    const glm::vec3 &Camera::getRotation() const
    {
        return m_transform.getLocalRotation();
    }

    //const glm::vec3 &Camera::getFront() const
    //{
    //    return m_transform.getFront();
    //}
//
    //const glm::vec3 &Camera::getUp() const
    //{
    //    return m_transform.getUp();
    //}
//
    //const glm::vec3 &Camera::getRight() const
    //{
    //    return m_transform.getRight();
    //}

    //float Camera::getRoll() const
    //{
    //    return m_transform.getRotation().x;
    //}

    //float Camera::getPitch() const
    //{
    //    return m_transform.getRotation().y;
    //}
//
    //float Camera::getYaw() const
    //{
    //    return m_transform.getRotation().z;
    //}

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

    void Camera::updateProjectionMatrix()
    {
        m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
    }

    void Camera::resetUpdateFlags()
    {
        m_hasChangedProjection = false;
    }

    bool Camera::hasChangedProjection() const
    {
        return m_hasChangedProjection;
    }
}