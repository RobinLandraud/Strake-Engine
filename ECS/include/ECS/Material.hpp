#pragma once

#include <ECS/Textures.hpp>
#include <ECS/Shaders.hpp>
#include <unordered_map>
#include <functional>
#include <optional>

namespace ECS {
    class Material {
        public:
            Material(const ShaderProgram &shaderProgram);
            ~Material() = default;
            Material(const Material &other) = delete;
            Material(Material &&other) = delete;
            Material &operator=(const Material &other) = delete;
            Material &operator=(Material &&other) = delete;

            void bind() const;
            void unbind() const;

            void addTexture(Texture &texture, const std::string &uniformName);

        private:
            const ShaderProgram &m_shaderProgram;
            std::unordered_map<std::string, std::optional<std::reference_wrapper<Texture>>> m_textures;
    };
}