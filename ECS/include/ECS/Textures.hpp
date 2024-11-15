#pragma once
#include "third_party/stb_image.h"
#include <GL/glew.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace ECS {
    class Texture {
        public:
            ~Texture();
            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;
            Texture& operator=(Texture&&) = delete;
            Texture(Texture&&) = delete;

            virtual void bind() = 0;
            virtual void unbind()= 0;
            [[nodiscard]] const GLuint getID() const;
            [[nodiscard]] const bool isLoaded() const;
        protected:
            Texture() = default;
            GLuint m_texture = 0;
    };

    class Texture2D : public Texture {
        public:
            explicit Texture2D(const std::string &path);
            ~Texture2D() = default;
            Texture2D(const Texture2D&) = delete;
            Texture2D& operator=(const Texture2D&) = delete;
            Texture2D& operator=(Texture2D&&) = delete;
            Texture2D(Texture2D&&) = delete;

            void bind() final;
            void unbind() final;
    };

    class Texture3D : public Texture {
        public:
            explicit Texture3D(const std::vector<std::string> &paths);
            ~Texture3D() = default;
            Texture3D(const Texture3D&) = delete;
            Texture3D& operator=(const Texture3D&) = delete;
            Texture3D& operator=(Texture3D&&) = delete;
            Texture3D(Texture3D&&) = delete;

            void bind() final;
            void unbind() final;
    };
}