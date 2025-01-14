#pragma once

#include <ECS/Component/Light/Light.hpp>
#include <ECS/Component/Light/LightType.hpp>
#include <ECS/Component/Transform.hpp>
#include <ECS/Component/MeshRenderer.hpp>

namespace Strake {
    class DirectionalLight : public Light
    {
        public:
            DirectionalLight(GameObject &parent);

            void setRotation(const glm::vec3 &rotation);
            void setDirection(const glm::vec3 &direction);

            [[nodiscard]] glm::vec3 getDirection() const;
            virtual void renderShadowMap(ShaderProgram &shaderProgram) final;
            glm::mat4 getShadowLightSpaceMatrix() const;

        private:
            Transform &r_transform; // for rotation
    };
}