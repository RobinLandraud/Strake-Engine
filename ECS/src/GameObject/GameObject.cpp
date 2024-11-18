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

    void GameObject::awake() {
        for (auto &component : m_components) {
            component.second->awake();
        }
        for (auto &child : m_children) {
            child.second->awake();
        }
    }

    void GameObject::start() {
        for (auto &component : m_components) {
            component.second->start();
        }
        for (auto &child : m_children) {
            child.second->start();
        }
    }

    void GameObject::update() {
        for (auto &component : m_components) {
            component.second->update();
        }
        for (auto &child : m_children) {
            child.second->update();
        }
    }

    void GameObject::fixedUpdate() {
        for (auto &component : m_components) {
            component.second->fixedUpdate();
        }
        for (auto &child : m_children) {
            child.second->fixedUpdate();
        }
    }

    void GameObject::lateUpdate() {
        for (auto &component : m_components) {
            component.second->lateUpdate();
        }
        for (auto &child : m_children) {
            child.second->lateUpdate();
        }
    }

    void GameObject::render() {
        for (auto &component : m_components) {
            component.second->render();
        }
        for (auto &child : m_children) {
            child.second->render();
        }
    }
}