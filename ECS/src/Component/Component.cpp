#include <iostream>
#include <ECS/Component.hpp>

namespace ECS {
    uint32_t Component::m_idCounter = 0;

    Component::Component(const std::string &name, std::unordered_map<std::string, ComponentHolder> &parentComponents)
        : m_id(m_idCounter++), m_name(name), m_parentComponents(parentComponents)
    {}

    void Component::awake() {
        for (auto &component : m_parentComponents)
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