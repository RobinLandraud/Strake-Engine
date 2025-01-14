#pragma once

#include <Strake/Texture/Texture.hpp>
#include <Strake/Texture/Texture2D.hpp>
#include <Strake/Texture/Texture3D.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

namespace Strake {
    class TextureManager {
        public:
            TextureManager() = default;
            ~TextureManager() = default;

            template <typename T, typename... Args>
            inline Texture &addTexture(const std::string &name, Args&&... args) {
                static_assert(std::is_base_of<Texture, T>::value, "T must be derived from Texture");

                m_textures[name] = std::make_unique<T>(std::forward<Args>(args)...);
                if (!m_textures[name]->isLoaded()) {
                    throw std::runtime_error("Failed to load texture");
                }
                return *m_textures[name];
            }

            Texture &getTexture(const std::string &name);
            void removeTexture(const std::string &name);
            void clear();
        private:
            std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
    };
}