#include <ECS/Component.hpp>
#include <ECS/GameObject.hpp>

namespace ECS {

    GameObject::GameObject(std::string name)
        : m_name(std::move(name))
    {}

    GameObject::~GameObject() {
        m_components.clear();
    }

    const std::string &GameObject::getName() const {
        return m_name;
    }

    void GameObject::addChild(const std::string &name) {
        if (m_children.find(name) != m_children.end()) {
            return;
        }
        m_children[name] = std::make_unique<GameObject>(name);
    }

    bool GameObject::removeChild(const std::string &name) {
        if (m_children.find(name) == m_children.end()) {
            return false;
        }
        m_children.erase(name);
        return true;
    }

    GameObject &GameObject::getChild(const std::string &name) {
        return *m_children.at(name);
    }

    std::optional<std::reference_wrapper<GameObject>> GameObject::findChild(const std::string &name) {
        if (m_children.find(name) == m_children.end()) {
            return std::nullopt;
        }
        return std::ref(*m_children.at(name));
    }
}