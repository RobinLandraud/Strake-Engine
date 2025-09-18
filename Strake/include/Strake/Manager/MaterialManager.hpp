#pragma once

#include <Strake/Material/Material.hpp>
#include <memory>

namespace Strake {
    class MaterialManager {
        public:
            MaterialManager() = default;
            ~MaterialManager() = default;
            Material &addMaterial(const std::string &name);
            Material &getMaterial(const std::string &name);
            void removeMaterial(const std::string &name);
            void clear();
        private:
            std::unordered_map<std::string, std::unique_ptr<Material>> m_materials;
    };
}