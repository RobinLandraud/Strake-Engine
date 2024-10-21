#pragma once
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <optional>

namespace ECS {
    class Component;

    class GameObject {
        public:
            GameObject(const std::string &name);
            ~GameObject();

            [[nodiscard]] const std::string &getName() const;
            
            template<typename T, typename... Args>
            short addComponent(Args&&... args) {
                if (!std::is_base_of<Component, T>::value) {
                    return -2;
                }
                if (m_components.find(typeid(T)) != m_components.end()) {
                    return -1;
                }
                m_components[typeid(T)] = std::make_unique<T>(*this, std::forward<Args>(args)...);
                return 0;
            }

            template<typename T>
            std::optional<std::reference_wrapper<T>> getComponent() {
                if (m_components.find(typeid(T)) == m_components.end()) {
                    return std::nullopt;
                }
                return std::ref(static_cast<T&>(*m_components[typeid(T)]));
            }

        private:
            std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
            const std::string m_name;
    };
}