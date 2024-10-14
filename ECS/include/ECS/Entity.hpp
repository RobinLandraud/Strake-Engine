#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <ECS/Component.hpp>

namespace ECS {
    class Entity {
        public:
            explicit Entity(const std::string &name);
            ~Entity() = default;
            const uint32_t getId() const;
            const std::string &getName() const;

            void awake();
            void start();
            void update();
            void fixedUpdate();
            void lateUpdate();
            void render();

            template<typename T, typename... Args>
            void addComponent(const std::string &name, Args &&... args) {
                if (m_components.find(name) != m_components.end()) {
                    throw std::runtime_error("Component already exists : " + name);
                }
                m_components.insert(std::make_pair(name, ComponentHolder(std::type_index(typeid(T)), std::make_unique<T>(name, m_components, std::forward<Args>(args)...))));
            }

            template<typename T>
            T &getComponent(const std::string &name) {
                if (m_components.find(name) == m_components.end()) {
                    throw std::runtime_error("Component not found : " + name);
                }
                if (m_components.at(name).type != std::type_index(typeid(T))) {
                    throw std::runtime_error("Component type mismatch : " + name);
                }
                return dynamic_cast<T &>(*m_components.at(name).component);
            }

        protected:
            const uint32_t m_id;
            const std::string m_name;
            std::unordered_map<std::string, ComponentHolder> m_components;

        private:
            static uint32_t m_idCounter;
    };
}