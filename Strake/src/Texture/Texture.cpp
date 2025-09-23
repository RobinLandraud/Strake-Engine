#include <Strake/Texture/Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb_image.h"

namespace Strake {
    Texture::~Texture() {
        if (m_texture != 0) {
            glDeleteTextures(1, &m_texture);
        }
    }

    GLuint Texture::getID() const {
        return m_texture;
    }

    bool Texture::isLoaded() const {
        return m_texture != 0;
    }
}