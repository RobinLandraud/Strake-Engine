#pragma once

#include <ECS/Component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ECS {
    enum class Space {
        LOCAL,
        WORLD
    };
    class Transform : public Component
    {
        public:
            Transform(GameObject &parent);
            //void lateUpdate() final; // update matrix

            //world space
            //void setPosition(const glm::vec3 &position);
            //void translate(const glm::vec3 &translation);

            void setRotation(const glm::vec3 &rotation);
            void rotate(const glm::vec3 &rotation);
            //void setRoll(float roll);
            //void setPitch(float pitch);
            //void setYaw(float yaw);

            //void setScale(const glm::vec3 &scale);
            //void scale(const glm::vec3 &scale);

            //local space
            void setLocalPosition(const glm::vec3 &position);
            void translateLocal(const glm::vec3 &translation);

            void setLocalRotation(const glm::vec3 &rotation);
            void rotateLocal(const glm::vec3 &rotation);
            void setLocalRoll(float roll);
            void setLocalPitch(float pitch);
            void setLocalYaw(float yaw);

            void setLocalScale(const glm::vec3 &scale);
            void scaleLocal(const glm::vec3 &scale);

            // get the position, rotation, scale in world space
            [[nodiscard]] const glm::vec3 &getLocalPosition() const; // get the position in local space
            [[nodiscard]] const glm::vec3 &getLocalRotation() const; // get the rotation in local space
            [[nodiscard]] const glm::vec3 &getLocalScale() const; // get the scale in local space
            [[nodiscard]] const glm::vec3 &getLocalFront() const; // get the front at this tick
            [[nodiscard]] const glm::vec3 &getLocalUp() const; // get the up at this tick
            [[nodiscard]] const glm::vec3 &getLocalRight() const; // get the right at this tick
            [[nodiscard]] const glm::mat4 &getLocalMatrix(); // get the matrix at this frame. deprecated if transform is not updated

            //[[nodiscard]] const glm::vec3 &getPosition() const; // get the position in world space
            //[[nodiscard]] const glm::vec3 &getRotation() const; // get the rotation in world space
            //[[nodiscard]] const glm::vec3 &getScale() const; // get the scale in world space
            //[[nodiscard]] const glm::vec3 &getFront() const; // get the front at this tick
            //[[nodiscard]] const glm::vec3 &getUp() const; // get the up at this tick
            //[[nodiscard]] const glm::vec3 &getRight() const; // get the right at this tick
            [[nodiscard]] const glm::mat4 &getWorldMatrix(); // get the matrix at this frame. deprecated if transform is not updated

        private:
            glm::mat4 m_localMatrix = glm::mat4(1.0f);
            glm::vec3 m_localPosition = glm::vec3(0.0f);
            glm::vec3 m_localRotation = glm::vec3(0.0f); // roll, pitch, yaw
            glm::vec3 m_localScale = glm::vec3(1.0f);
            
            glm::vec3 m_localUp = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 m_localFront = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 m_localRight = glm::vec3(1.0f, 0.0f, 0.0f);

            glm::mat4 m_worldMatrix = glm::mat4(1.0f);
            glm::vec3 m_worldPosition = glm::vec3(0.0f);
            glm::vec3 m_worldRotation = glm::vec3(0.0f); // used for rotation around object center (even if translation is not at 0, 0, 0)
            glm::vec3 m_worldScale = glm::vec3(1.0f);

            glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::vec3 m_worldFront = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 m_worldRight = glm::vec3(1.0f, 0.0f, 0.0f);

            //void updateEulerAngles();

            bool m_worldDirty = false; // if the transform needs to be updated (dirty / lazy update)
            bool m_localDirty = false; // if the transform needs to be updated (dirty / lazy update)
            void setWorldDirty();
            void updateLocalMatrix();
            void updateWorldMatrix();
            void updateEulerAngles();
    };
}