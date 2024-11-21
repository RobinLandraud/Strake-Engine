#pragma once
#include <memory>
#include <optional>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace ECS {
    class Component;
    class Camera;
    class Script;

    class GameObject {
        public:
            explicit GameObject(std::string name);
            ~GameObject();
            GameObject(const GameObject&) = delete;
            GameObject& operator=(const GameObject&) = delete;
            GameObject& operator=(GameObject&&) = delete;
            GameObject(GameObject&&) = delete;

            [[nodiscard]] const std::string &getName() const;
            [[nodiscard]] std::type_index getDerivedType(Component &component) const;
            
            template<typename T, typename... Args>
            short addComponent(Args&&... args) {
                if (!std::is_base_of<Component, T>::value) {
                    std::cerr << "Component must derive from Component class" << std::endl;
                    return -2;
                }
                if (m_components.find(typeid(T)) != m_components.end()) {
                    std::cerr << "Component already added" << std::endl;
                    return -1;
                }
                std::unique_ptr<T> component = std::make_unique<T>(*this, std::forward<Args>(args)...);
                std::type_index devType = getDerivedType(*component);
                if (devType != typeid(Script)) {
                    for (auto &derivedType : m_derivedTypes) {
                        if (derivedType == devType) {
                            std::cerr << "Component already added" << std::endl;
                            return -1;
                        }
                    }
                    m_derivedTypes.push_back(devType);
                }
                m_components[typeid(T)] = std::move(component);
                return 0;
            }

            template<typename T>
            std::optional<std::reference_wrapper<T>> findComponent() {
                for (auto &component : m_components) {
                    if (component.first == typeid(T)) {
                        return std::ref(static_cast<T&>(*component.second));
                    } else if (T *derived = dynamic_cast<T*>(component.second.get())) {
                        return std::ref(*derived);
                    }
                }
            }

            template<typename T>
            T &getComponent() {
                for (auto &component : m_components) {
                    if (component.first == typeid(T)) {
                        return static_cast<T&>(*component.second);
                    } else if (T *derived = dynamic_cast<T*>(component.second.get())) {
                        return *derived;
                    }
                }
                throw std::runtime_error("Component not found");
            }

            template<typename T>
            short removeComponent() {
                if (m_components.find(typeid(T)) == m_components.end()) {
                    std::cerr << "Component not found" << std::endl;
                    return -1;
                }
                std::type_index derivedType = getDerivedType(*m_components[typeid(T)]);
                m_components.erase(typeid(T));
                m_derivedTypes.erase(std::remove(m_derivedTypes.begin(), m_derivedTypes.end(), derivedType), m_derivedTypes.end());
                return 0;
            }

            void addChild(const std::string &name);
            bool removeChild(const std::string &name);
            GameObject &getChild(const std::string &name);
            std::optional<std::reference_wrapper<GameObject>> findChild(const std::string &name);

            template<typename T>
            T &getComponentInChildren() {
                for (auto &child : m_children) {
                    auto component = child.second->findComponent<T>();
                    if (component.has_value()) {
                        return component.value().get();
                    }
                }
            }

            template<typename T>
            std::vector<std::reference_wrapper<T>> getComponentsInChildren() {
                std::vector<std::reference_wrapper<T>> components;
                for (auto &child : m_children) {
                    auto component = child.second->findComponent<T>();
                    if (component.has_value()) {
                        components.push_back(component.value().get());
                    }
                }
                return components;
            }

            template<typename T>
            std::optional<std::reference_wrapper<T>> findComponentInChildren() {
                for (auto &child : m_children) {
                    auto component = child.second->findComponent<T>();
                    if (component.has_value()) {
                        return component;
                    }
                }
                return std::nullopt;
            }

            void awake();
            void start();
            void update();
            void fixedUpdate();
            void lateUpdate();
            void render(Camera &camera);

        private:
            std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;
            std::vector<std::type_index> m_derivedTypes;
            std::unordered_map<std::string, std::unique_ptr<GameObject>> m_children;
            const std::string m_name;
    };
}