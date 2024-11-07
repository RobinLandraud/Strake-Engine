#pragma once
#include "third_party/stb_image.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>

namespace ECS {
    class Texture {
        public:
            ~Texture();
            virtual void bind() = 0;
            virtual void unbind()= 0;
            [[nodiscard]] const GLuint getID() const;
            [[nodiscard]] const bool isLoaded() const;
        protected:
            GLuint m_texture;
    };

    class Texture2D : public Texture {
        public:
            Texture2D(const std::string &path);
            ~Texture2D() = default;
            virtual void bind() final;
            virtual void unbind() final;
    };

    class Texture3D : public Texture {
        public:
            Texture3D(const std::vector<std::string> &paths);
            ~Texture3D() = default;
            virtual void bind() final;
            virtual void unbind() final;
    };
}