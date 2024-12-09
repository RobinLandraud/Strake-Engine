#pragma once

#include <ECS/Component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ECS {
    class Camera : public Component
    {
        public:
            Camera(GameObject &parent);

            void lateUpdate() final; // update matrix

            void setProjection(float fov, float aspect, float near, float far);

            //void translate(const glm::vec3 &translation);
            //void setPosition(const glm::vec3 &position);

            //void rotate(float roll, float pitch, float yaw);
            //void rotate(const glm::vec3 &rotation);
            //void setFront(const glm::vec3 &front);
            //void setUp(const glm::vec3 &up);
            //void setRight(const glm::vec3 &right);
            //void setRoll(float roll);
            //void setPitch(float pitch);
            //void setYaw(float yaw);

            void setFov(float fov);
            void setAspect(float aspect);
            void setNear(float near);
            void setFar(float far);

            void resetUpdateFlags(); // reset the update flags
            
            [[nodiscard]] const glm::mat4 &getViewMatrix(); // get the view matrix at this frame. deprecated if transform is not updated
            [[nodiscard]] const glm::mat4 &getProjectionMatrix() const; // get the projection matrix at this frame. deprecated if transform is not updated
            
            [[nodiscard]] const glm::vec3 &getPosition() const; // get the position at this tick
            
            [[nodiscard]] const glm::vec3 &getRotation() const; // get the rotation at this tick
            //[[nodiscard]] const glm::vec3 &getFront() const; // get the front at this tick
            //[[nodiscard]] const glm::vec3 &getUp() const; // get the up at this tick
            //[[nodiscard]] const glm::vec3 &getRight() const; // get the right at this tick
            //[[nodiscard]] float getRoll() const; // get the roll at this tick
            //[[nodiscard]] float getPitch() const; // get the pitch at this tick
            //[[nodiscard]] float getYaw() const; // get the yaw at this tick

            [[nodiscard]] float getFov() const; // get the fov at this tick
            [[nodiscard]] float getAspect() const; // get the aspect at this tick
            [[nodiscard]] float getNear() const; // get the near at this tick
            [[nodiscard]] float getFar() const; // get the far at this tick

            [[nodiscard]] bool hasChangedProjection() const; // check if the projection matrix has changed
        
        private:
            void updateProjectionMatrix();

            Transform &m_transform;

            // model matrix
            glm::mat4 m_viewMatrix = glm::mat4(1.0f);
            glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
            bool m_projectionNeedUpdate = false;

            // projection matrix
            float m_fov = 45.0f;
            float m_aspect = 1.0f;
            float m_near = 0.1f;
            float m_far = 100.0f;

            bool m_hasChangedProjection = true;
    };
}