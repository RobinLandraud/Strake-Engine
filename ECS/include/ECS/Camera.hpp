#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ECS/Component.hpp>

namespace ECS {
    class Camera : public Component
    {
        public:
            using ECS::Component::Component;
            
            virtual void lateUpdate() final; // update matrix
            
            void setProjection(float fov, float aspect, float near, float far);
            void setPosition(const glm::vec3 &position);
            void setFront(const glm::vec3 &front);
            void setUp(const glm::vec3 &up);
            void setRoll(float roll);
            void setPitch(float pitch);
            void setYaw(float yaw);
            void translate(const glm::vec3 &translation);
            void rotate(float roll, float pitch, float yaw);
            void rotate(const glm::vec3 &rotation);
            void setFov(float fov);
            void setAspect(float aspect);
            void setNear(float near);
            void setFar(float far);
            
            [[nodiscard]] const glm::mat4 &getViewMatrix() const; // get the view matrix at this frame. deprecated if transform is not updated
            [[nodiscard]] const glm::mat4 &getProjectionMatrix() const; // get the projection matrix at this frame. deprecated if transform is not updated
            [[nodiscard]] const glm::vec3 &getPosition() const; // get the position at this tick
            [[nodiscard]] const glm::vec3 &getFront() const; // get the front at this tick
            [[nodiscard]] const glm::vec3 &getUp() const; // get the up at this tick
            [[nodiscard]] float getRoll() const; // get the roll at this tick
            [[nodiscard]] float getPitch() const; // get the pitch at this tick
            [[nodiscard]] float getYaw() const; // get the yaw at this tick
            [[nodiscard]] float getFov() const; // get the fov at this tick
            [[nodiscard]] float getAspect() const; // get the aspect at this tick
            [[nodiscard]] float getNear() const; // get the near at this tick
            [[nodiscard]] float getFar() const; // get the far at this tick
        
        private:
            void updateViewMatrix();
            void updateProjectionMatrix();

            // model matrix
            glm::mat4 m_viewMatrix = glm::mat4(1.0f);
            glm::mat4 m_projectionMatrix = glm::mat4(1.0f);
            bool m_viewNeedUpdate = false;
            bool m_projectionNeedUpdate = false;

            // position
            glm::vec3 m_position = glm::vec3(0.0f);
            
            // euler angles
            glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);

            // rotations
            float m_roll = 0.0f;
            float m_pitch = 0.0f;
            float m_yaw = 0.0f;

            // projection matrix
            float m_fov = 45.0f;
            float m_aspect = 1.0f;
            float m_near = 0.1f;
            float m_far = 100.0f;

            bool needUpdate = false;
    };
}