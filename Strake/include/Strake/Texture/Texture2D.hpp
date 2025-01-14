#pragma once

#include <Strake/Texture/Texture.hpp>
#include <iostream>

namespace Strake {
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
}