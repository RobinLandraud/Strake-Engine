#include <ECS/Material.hpp>

namespace ECS {
    Material::Material(const ShaderProgram &shaderProgram) :
    m_shaderProgram(shaderProgram)
    {}

    void Material::bind() const {
        int textureUnit = 0;
        for (const auto &pair : m_textures) {
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            if (!pair.second.has_value()) {
                textureUnit++;
                continue;
            }
            pair.second.value().get().bind();
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
    }

    void Material::addTexture(Texture &texture, const std::string &uniformName) {
        m_textures[uniformName] = std::ref(texture);
    }

    ShaderProgram &Material::getShaderProgram() const {
        return const_cast<ShaderProgram &>(m_shaderProgram);
    }
}