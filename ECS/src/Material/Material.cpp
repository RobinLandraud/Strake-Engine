#include <ECS/Material.hpp>

namespace ECS {
    Material::Material() :
    m_shaderProgram(
        ShaderProgram(
            "ECS/src/Shader/glsl/texture2D/vertex.glsl",
            "ECS/src/Shader/glsl/texture2D/fragment.glsl"
        )
    )
    {
        getShaderProgram().use();
        getShaderProgram().setUniform("textureSampler", 0); // default texture unit

        getShaderProgram().setUniform("ambientIntensity", 0.1f); // global to every object
        
        getShaderProgram().setUniform("shininess", 32.0f);
        getShaderProgram().setUniform("alphaThreshold", 0.01f);
        // Set default light (To be removed)
        getShaderProgram().setUniform("light.position", glm::vec3(10.0f, 1.0f, 0.0f));
        getShaderProgram().setUniform("light.color", glm::vec3(1.0f, 1.0f, 1.0f));
        getShaderProgram().setUniform("light.intensity", 1.0f);
    }

    Material::Material(const std::string &vertexPath, const std::string &fragmentPath) :
    m_shaderProgram(
        ShaderProgram(vertexPath, fragmentPath)
    )
    {
        getShaderProgram().use();
        getShaderProgram().setUniform("textureSampler", 0); // default texture unit

        getShaderProgram().setUniform("ambientIntensity", 0.1f); // global to every object
        
        getShaderProgram().setUniform("shininess", 32.0f);
        getShaderProgram().setUniform("alphaThreshold", 0.01f);
        // Set default light (To be removed)
        getShaderProgram().setUniform("light.position", glm::vec3(10.0f, 1.0f, 0.0f));
        getShaderProgram().setUniform("light.color", glm::vec3(1.0f, 1.0f, 1.0f));
        getShaderProgram().setUniform("light.intensity", 1.0f);
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
            std::cout << "Texture " << pair.second.value().get().getID() << " bind to texture unit " << textureUnit << std::endl;
            std::cout << "Binding texture " << pair.first << " to shader unit " << textureUnit << std::endl;
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