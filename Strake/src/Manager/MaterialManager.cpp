#include <Strake/Manager/MaterialManager.hpp>

namespace Strake {
    Material &MaterialManager::addMaterial(const std::string &name) {
        m_materials[name] = std::make_unique<Material>();
        return *m_materials[name];
    }

    Material &MaterialManager::getMaterial(const std::string &name) {
        return *m_materials.at(name);
    }

    void MaterialManager::removeMaterial(const std::string &name) {
        m_materials.erase(name);
    }

    void MaterialManager::clear() {
        m_materials.clear();
    }
}