#include <ECS/EntityManager.hpp>

namespace ECS {

    short EntityManager::addEntity(const EntityTag &name) {
        if (m_entities.find(name) != m_entities.end()) {
            return -1;
        }
        m_entities.insert(std::make_pair(name, std::unordered_map<std::string, ComponentHolder>()));
        return 0;
    }

    short EntityManager::removeEntity(const EntityTag &name) {
        if (m_entities.find(name) == m_entities.end()) {
            return -1;
        }
        m_entities.erase(name);
        return 0;
    }

    short EntityManager::removeComponent(const EntityTag &entity, const ComponentTag &name) {
        if (m_entities.find(entity) == m_entities.end()) {
            return -1;
        }
        if (m_entities[entity].find(name) == m_entities[entity].end()) {
            return -1;
        }
        m_entities[entity].erase(name);
        return 0;
    }
}