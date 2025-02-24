#pragma once

#include <Strake/Component/Component.hpp>
#include <Strake/Dispatcher/EventDispatcher.hpp>
#include <Strake/Dispatcher/EventData.hpp>
#include <Strake/Component/Light/ShadowMap.hpp>
#include <Strake/Component/Light/LightType.hpp>
#include <Strake/Shader/ShaderProgram.hpp>
#include <Strake/Layer/CullingMask.hpp>

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

            
            [[nodiscard]] CullingMask &getCullingMask();
            
        protected:
            
            explicit Light(GameObject &parent, LightType type);
            ~Light() override;

            LightType m_type;

            glm::vec3 m_color;
            float m_intensity;
            float m_minIntensity;

            ShadowMap m_shadowMap;

            CullingMask m_cullingMask;
    };
}