#pragma once

#include <ECS/Texture/Texture.hpp>
#include <vector>
#include <string>
#include <iostream>

namespace Strake {
    class Texture3D : public Texture {
        public:
            explicit Texture3D(const std::vector<std::string> &paths);
            ~Texture3D() = default;
            Texture3D(const Texture3D&) = delete;
            Texture3D& operator=(const Texture3D&) = delete;
            Texture3D& operator=(Texture3D&&) = delete;
            Texture3D(Texture3D&&) = delete;

            void bind() final; // not implemented
            void unbind() final; // not implemented
    };
}