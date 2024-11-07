#pragma once
#include <memory>
#include <optional>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace ECS {
    class Component;

    class GameObject {
        public:
            explicit GameObject(const std::string &name);
            ~GameObject();
            GameObject(const GameObject&) = delete;
            GameObject& operator=(const GameObject&) = delete;
            GameObject& operator=(GameObject&&) = delete;
            GameObject(GameObject&&) = delete;

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
            std::optional<std::reference_wrapper<T>> findComponent() const {
                if (m_components.find(typeid(T)) == m_components.end()) {
                    return std::nullopt;
                }
                return std::ref(static_cast<T&>(*m_components.at(typeid(T))));
            }

            template<typename T>
            T &getComponent() const {
                return static_cast<T&>(*m_components.at(typeid(T)));
            }

            template<typename T>
            bool removeComponent() {
                if (m_components.find(typeid(T)) == m_components.end()) {
                    return false;
                }
                m_components.erase(typeid(T));
                return true;
            }

        private:
            std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
            const std::string m_name;
    };
}