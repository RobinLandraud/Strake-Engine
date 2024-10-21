#include <ECS/GameObject.hpp>
#include <ECS/Component.hpp>

namespace ECS {

    GameObject::GameObject(const std::string &name)
        : m_name(name)
    {}

    GameObject::~GameObject() {
        m_components.clear();
    }

    const std::string &GameObject::getName() const {
        return m_name;
    }
}