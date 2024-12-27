#pragma once

#include <ECS/Component.hpp>
#include <ECS/Transform.hpp>
#include <ECS/EventDispatcher.hpp>

namespace ECS {
    enum class LightType {
        Directional,
        Point,
        Spot
    };

    class Light: public Component
    {
        public:
            void setColor(const glm::vec3 &color);
            void setIntensity(float intensity);
            void setMinIntensity(float minIntensity);

            [[nodiscard]] float getIntensity() const;
            [[nodiscard]] float getMinIntensity() const;
            [[nodiscard]] const glm::vec3 &getColor() const;
            [[nodiscard]] LightType getType() const;

        protected:

            explicit Light(GameObject &parent, LightType type);
            ~Light() override;

            LightType m_type;

            glm::vec3 m_color;
            float m_intensity;
            float m_minIntensity;
    };

    class PointLight : public Light
    {
        public:
            PointLight(GameObject &parent);

            void setPosition(const glm::vec3 &position);

            [[nodiscard]] const glm::vec3 getPosition() const;

        private:
            Transform &r_transform; // for position
    };

    class DirectionalLight : public Light
    {
        public:
            DirectionalLight(GameObject &parent);

            void setRotation(const glm::vec3 &rotation);
            void setDirection(const glm::vec3 &direction);

            [[nodiscard]] glm::vec3 getDirection() const;

        private:
            Transform &r_transform; // for rotation
    };
}