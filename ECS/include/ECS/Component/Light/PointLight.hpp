#pragma once

#include <ECS/Component/Light/Light.hpp>
#include <ECS/Component/Light/LightType.hpp>
#include <ECS/Component/Transform.hpp>

namespace Strake {
    class PointLight : public Light
    {
        public:
            PointLight(GameObject &parent);

            void setPosition(const glm::vec3 &position);

            [[nodiscard]] const glm::vec3 getPosition() const;

        private:
            Transform &r_transform; // for position
    };
}