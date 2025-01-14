#pragma once

#include <ECS/Component.hpp>
#include <ECS/EventDispatcher.hpp>
#include <ECS/Component/Light/ShadowMap.hpp>
#include <ECS/Component/Light/LightType.hpp>
#include <ECS/Shader/ShaderProgram.hpp>

namespace Strake {
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

            virtual void renderShadowMap(ShaderProgram &shaderProgram);
            [[nodiscard]] ShadowMap &getShadowMap();
            [[nodiscard]] const ShadowMap &getShadowMap() const;

        protected:

            explicit Light(GameObject &parent, LightType type);
            ~Light() override;

            LightType m_type;

            glm::vec3 m_color;
            float m_intensity;
            float m_minIntensity;

            ShadowMap m_shadowMap;
    };
}