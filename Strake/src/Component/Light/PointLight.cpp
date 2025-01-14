#pragma once

#include <Strake/Component/Light/PointLight.hpp>

namespace Strake {
    PointLight::PointLight(GameObject &parent) :
        Light(parent, LightType::Point),
        r_transform(parent.getTransform())
    {
    }

    void PointLight::setPosition(const glm::vec3 &position) {
        r_transform.setLocalPosition(position);
    }

    const glm::vec3 PointLight::getPosition() const {
        return r_transform.getWorldPosition();
    }
}