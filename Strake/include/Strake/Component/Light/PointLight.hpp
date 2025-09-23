#pragma once

#include <Strake/Component/Light/Light.hpp>
#include <Strake/Component/Light/LightType.hpp>
#include <Strake/Component/Transform.hpp>

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