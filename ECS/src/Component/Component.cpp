#include <iostream>
#include <ECS/Component.hpp>

namespace ECS {

    Component::Component(
        const std::string &name,
        const std::string &parent,
        std::unordered_map<EntityTag, std::unordered_map<std::string, ComponentHolder>> &entities
        )
        : m_name(name), m_parent(parent), r_entities(entities)
    {}

    void Component::awake() {
        for (auto &component : r_entities[m_parent])
        {
            std::cout << component.first << std::endl;
        }
    }
    void Component::start() {}
    void Component::update() {}
    void Component::fixedUpdate() {}
    void Component::lateUpdate() {}
    void Component::render() {}
}