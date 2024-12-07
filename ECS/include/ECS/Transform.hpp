#pragma once

#include <ECS/Component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ECS {
    class Transform : public Component
    {
        public:
            Transform(GameObject &parent);
            void lateUpdate() final; // update matrix

            void setPosition(const glm::vec3 &position);
            void translate(const glm::vec3 &translation);

            void setRotation(const glm::vec3 &rotation);
            void rotate(const glm::vec3 &rotation);
            void setRoll(float roll);
            void setPitch(float pitch);
            void setYaw(float yaw);

            void setScale(const glm::vec3 &scale);
            void scale(const glm::vec3 &scale);

            [[nodiscard]] const glm::mat4 &getMatrix(); // get the matrix at this frame. deprecated if transform is not updated

            [[nodiscard]] const glm::vec3 &getPosition() const; // get the position at this tick

            [[nodiscard]] const glm::vec3 &getRotation() const; // get the rotation at this tick
            [[nodiscard]] const glm::vec3 &getFront() const; // get the front at this tick
            [[nodiscard]] const glm::vec3 &getUp() const; // get the up at this tick
            [[nodiscard]] const glm::vec3 &getRight() const; // get the right at this tick

            [[nodiscard]] const glm::vec3 &getScale() const; // get the scale at this tick
        private:
            glm::mat4 m_matrix = glm::mat4(1.0f);
            glm::vec3 m_position = glm::vec3(0.0f);
            glm::vec3 m_rotation = glm::vec3(0.0f); // roll, pitch, yaw
            glm::vec3 m_scale = glm::vec3(1.0f);

            void updateEulerAngles();
            glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);

            bool needUpdate = false;
            void updateMatrix();
    };
}