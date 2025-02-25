#include <Strake/Component/Component.hpp>
#include <Strake/GameObject/GameObject.hpp>
#include <Strake/Scene/Scene.hpp>
#include <Strake/Manager/LayerManager.hpp>
#include <Strake/Component/Script.hpp>
#include <Strake/Component/Transform.hpp>

namespace Strake {

    GameObject::GameObject(std::string name, const Scene &scene, EventDispatcher &eventDispatcher, const Layer &layer) :
        m_name(std::move(name)),
        m_eventDispatcher(eventDispatcher),
        r_layer(layer),
        r_scene(scene)
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
        m_children[name] = std::make_unique<GameObject>(name, r_scene, m_eventDispatcher, r_layer.get());
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

    bool GameObject::isScript(std::type_index type) const {
        return std::type_index(typeid(Script)) == type;
    }

    EventDispatcher &GameObject::getEventDispatcher() {
        return m_eventDispatcher;
    }

    void GameObject::setLayer(std::string &&name) {
        setLayer(r_scene.getLayerManager().getLayer(name));
    }

    void GameObject::setLayer(int priority) {
        setLayer(r_scene.getLayerManager().getLayer(priority));
    }

    void GameObject::setLayer(const Layer &layer) {
        int oldLayer = r_layer.get().getPriority();
        r_layer = layer;
        updateLayers(oldLayer);
    }

    const LayerManager &GameObject::getLayerManager() const {
        return r_scene.getLayerManager();
    }

    void GameObject::updateLayers(int oldLayer) {
        std::optional<std::reference_wrapper<Renderer>> renderer = findComponent<Renderer>();
        if (renderer.has_value()) {
            renderer.value().get().updateLayer(oldLayer);
        }
    }

    const Layer &GameObject::getLayer() const {
        return r_layer.get();
    }
}