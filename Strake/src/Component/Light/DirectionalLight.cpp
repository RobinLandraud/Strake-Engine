#include <Strake/Component/Light/DirectionalLight.hpp>

namespace Strake {
    DirectionalLight::DirectionalLight(GameObject &parent) :
        Light(parent, LightType::Directional),
        r_transform(parent.getTransform())
    {
    }

    void DirectionalLight::setRotation(const glm::vec3 &rotation) {
        // set the rotation in local space
        r_transform.setLocalRotation(rotation);
    }

    void DirectionalLight::setDirection(const glm::vec3 &direction) {
        r_transform.setLocalPitch(glm::degrees(asin(direction.y)));
        r_transform.setLocalYaw(glm::degrees(atan2(direction.x, direction.z)));
    }

    glm::vec3 DirectionalLight::getDirection() const {
        const glm::mat4 &mat = r_transform.getWorldMatrix();
        return glm::normalize(-glm::vec3( // must be transform class value (only updated if needed)
            mat[1][0], mat[1][1], mat[1][2]
        ));
    }

    glm::mat4 DirectionalLight::getShadowLightSpaceMatrix() const {
        float farPlane = 150.0f;
        return m_shadowMap.getLightProjection() * glm::lookAt(
            -getDirection() * farPlane, // position
            glm::vec3(0.0f), // target
            glm::vec3(0.0f, 1.0f, 0.0f) // up
        );
    }

    void DirectionalLight::renderShadowMap(ShaderProgram &shaderProgram) {
        m_shadowMap.bind();
        shaderProgram.setUniform("lightSpaceMatrix", getShadowLightSpaceMatrix());
        for (auto &object : m_shadowMap.getObjects()) {
            shaderProgram.setUniform("model", object.get().getTransform().getWorldMatrix());
            object.get().getComponent<MeshRenderer>().GLrender();
        }
        m_shadowMap.unbind();
    }
}

