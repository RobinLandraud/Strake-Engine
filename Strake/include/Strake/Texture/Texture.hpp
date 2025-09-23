#pragma once

#include "third_party/stb_image.h"
#include <GL/glew.h>

namespace Strake {
    class Texture {
        public:
            Texture() = default;
            ~Texture();
            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;
            Texture& operator=(Texture&&) = delete;
            Texture(Texture&&) = delete;

            virtual void bind() {};
            virtual void unbind() {};
            [[nodiscard]] GLuint getID() const;
            [[nodiscard]] bool isLoaded() const;
        protected:
            GLuint m_texture = 0;
    };
}