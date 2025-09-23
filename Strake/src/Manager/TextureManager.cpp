#include <Strake/Manager/TextureManager.hpp>

namespace Strake {
    Texture &TextureManager::getTexture(const std::string &name) {
        return *m_textures.at(name);
    }

    void TextureManager::removeTexture(const std::string &name) {
        m_textures.erase(name);
    }

    void TextureManager::clear() {
        m_textures.clear();
    }
}