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

            [[nodiscard]] float getIntensity() const;
            [[nodiscard]] const glm::vec3 &getColor() const;

        protected:

            explicit Light(GameObject &parent, LightType type);
            ~Light() override;

            LightType m_type;
            glm::vec3 m_color;
            float m_intensity;
    };

    class PointLight : public Light
    {
        public:
            PointLight(GameObject &parent);

            void setPosition(const glm::vec3 &position);
            void setConstant(float constant);
            void setLinear(float linear);
            void setQuadratic(float quadratic);

            [[nodiscard]] const glm::vec3 getPosition() const;
            [[nodiscard]] float getConstant() const;
            [[nodiscard]] float getLinear() const;
            [[nodiscard]] float getQuadratic() const;

        private:
            Transform &r_transform;

            // Attenuation : I = 1 / (constant + linear * d + quadratic * d^2)
            float m_constant; //  base factor that does not change with distance
            float m_linear; // factor that is multiplied by the distance
            float m_quadratic; // factor that is multiplied by the square of the distance
    };
}