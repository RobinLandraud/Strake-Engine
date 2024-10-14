#pragma once
#include <ECS/Entity.hpp>
#include <ECS/Component.hpp>

namespace ECS {

    class EntityManager {
        public:
            EntityManager() = default;
            ~EntityManager() = default;

            short addEntity(const EntityTag &name);

            short removeEntity(const EntityTag &name);

            template<typename T, typename... Args>
            short addComponent(const EntityTag &entity, const ComponentTag &name, Args&&... args) {
                if (m_entities.find(entity) == m_entities.end()) {
                    return -1; // Entity not found
                }
                if (m_entities[entity].find(name) != m_entities[entity].end()) {
                    return -1; // Component already exists
                }
                m_entities[entity].insert(
                    std::make_pair(
                        name,
                        ComponentHolder(
                            typeid(T),
                            std::make_unique<T>(name, entity, m_entities, std::forward<Args>(args)...)
                        )
                    )
                );
                return 0;
            }

            std::optional<std::reference_wrapper<std::unordered_map<std::string, ComponentHolder>>> getComponents(const EntityTag &name) {
                if (m_entities.find(name) == m_entities.end()) {
                    return std::nullopt;
                }
                return std::ref(m_entities[name]);
            }

            template<typename T>
            std::optional<std::reference_wrapper<T>> getComponent(const EntityTag &entity, const ComponentTag &name) {
                if (m_entities.find(entity) == m_entities.end()) {
                    return std::nullopt;
                }
                if (m_entities[entity].find(name) == m_entities[entity].end()) {
                    return std::nullopt;
                }
                if (m_entities[entity].at(name).type != typeid(T)) {
                    return std::nullopt;
                }
                return std::ref(dynamic_cast<T&>(*m_entities.at(entity).at(name).component));
            }

            short removeComponent(const EntityTag &entity, const ComponentTag &name);

        private:
            std::unordered_map<EntityTag, std::unordered_map<std::string, ComponentHolder>> m_entities;
    };
}