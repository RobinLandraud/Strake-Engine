#include <ECS/Textures.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb_image.h"


namespace ECS {
    Texture::~Texture() {
        if (m_texture != 0) {
            glDeleteTextures(1, &m_texture);
        }
    }

    const GLuint Texture::getID() const {
        return m_texture;
    }

    const bool Texture::isLoaded() const {
        return m_texture != 0;
    }
}