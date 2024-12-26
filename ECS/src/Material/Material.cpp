#include <ECS/Material.hpp>

namespace ECS {
    Material::Material() :
        Material(
            "ECS/src/Shader/glsl/texture2D/vertex.glsl",
            "ECS/src/Shader/glsl/texture2D/fragment.glsl"
        )
    {
    }

    Material::Material(const std::string &vertexPath, const std::string &fragmentPath) :
    m_shaderProgram(
        ShaderProgram(vertexPath, fragmentPath)
    )
    {
        getShaderProgram().use();
        getShaderProgram().setUniform("textureSampler", 0); // default texture unit
        getShaderProgram().setUniform("ambientIntensity", 0.1f); // global to every object
        getShaderProgram().setUniform("shininess", 32.0f); // default shininess
        getShaderProgram().setUniform("alphaThreshold", 0.01f); // default alpha threshold
    }

    void Material::bind() const {
        getShaderProgram().use();
        int textureUnit = 0;
        for (const auto &pair : m_textures) {
            if (!pair.second.has_value()) {
                textureUnit++;
                continue;
            }
            // Set the texture unit
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            // Bind the texture to the texture unit
            pair.second.value().get().bind();
            // Set the uniform to the texture unit
            m_shaderProgram.setUniform(pair.first, textureUnit);
            textureUnit++;
        }
    }

    void Material::unbind() const {
        int textureUnit = 0;
        for (const auto &pair : m_textures) {
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            if (!pair.second.has_value()) {
                glBindTexture(GL_TEXTURE_2D, 0);
                textureUnit++;
                continue;
            }
            pair.second.value().get().unbind();
            textureUnit++;
        }
        getShaderProgram().unuse(); // only for debug
    }

    void Material::addTexture(Texture &texture, const std::string &uniformName) {
        m_textures[uniformName] = std::ref(texture);
    }

    void Material::setAlphaThreshold(float alphaThreshold) {
        m_alphaThreshold = alphaThreshold;
        getShaderProgram().use();
        getShaderProgram().setUniform("alphaThreshold", alphaThreshold);
    }

    float Material::getAlphaThreshold() const {
        return m_alphaThreshold;
    }

    void Material::setShininess(float shininess) {
        m_shininess = shininess;
        getShaderProgram().use();
        getShaderProgram().setUniform("shininess", shininess);
    }

    float Material::getShininess() const {
        return m_shininess;
    }

    ShaderProgram &Material::getShaderProgram() const {
        return const_cast<ShaderProgram &>(m_shaderProgram);
    }
}