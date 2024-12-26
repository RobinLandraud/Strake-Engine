#include <ECS/Component.hpp>
#include <ECS/GameObject.hpp>
#include <ECS/Scene.hpp>
#include <ECS/Script.hpp>
#include <ECS/Transform.hpp>

namespace ECS {

    GameObject::GameObject(std::string name, EventDispatcher &eventDispatcher) :
        m_name(std::move(name)),
        m_eventDispatcher(eventDispatcher)
    {
        m_components[typeid(Transform)] = std::make_unique<Transform>(*this);
        m_transform = static_cast<Transform &>(*m_components[typeid(Transform)]);
        m_derivedTypes.push_back(typeid(Transform));
    }

    GameObject::~GameObject() {
        m_components.clear();
    }

    const std::string &GameObject::getName() const {
        return m_name;
    }

    std::type_index GameObject::getDerivedType(Component &component) const {
        return component.getDerivedType();
    }

    GameObject &GameObject::addChild(const std::string &name) {
        if (m_children.find(name) != m_children.end()) {
            throw std::runtime_error("Child already exists: " + name);
        }
        m_children[name] = std::make_unique<GameObject>(name, m_eventDispatcher);
        m_children[name].get()->m_parent = *this;
        return *m_children[name];
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

    const std::unordered_map<std::string, std::unique_ptr<GameObject>> &GameObject::getChildren() const {
        return m_children;
    }

    std::optional<std::reference_wrapper<GameObject>> GameObject::findChild(const std::string &name) {
        if (m_children.find(name) == m_children.end()) {
            return std::nullopt;
        }
        return std::ref(*m_children.at(name));
    }

    const std::unordered_map<std::type_index, std::unique_ptr<Component>> &GameObject::getComponents() const {
        return m_components;
    }

    Transform &GameObject::getTransform() {
        return m_transform.value().get();
    }

    bool GameObject::hasParent() const {
        return m_parent.has_value();
    }

    GameObject &GameObject::getParent() const {
        if (!m_parent.has_value()) {
            throw std::runtime_error("Parent is null");
        }
        return *m_parent;
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

    void GameObject::render(Camera &camera) {
        for (auto &component : m_components) {
            component.second->render(camera);
        }
        for (auto &child : m_children) {
            child.second->render(camera);
        }
    }

    bool GameObject::isScript(std::type_index type) const {
        return std::type_index(typeid(Script)) == type;
    }

    EventDispatcher &GameObject::getEventDispatcher() {
        return m_eventDispatcher;
    }
}