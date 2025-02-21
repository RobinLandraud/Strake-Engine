#include <Strake/Component/Component.hpp>
#include <Strake/GameObject/GameObject.hpp>
#include <Strake/Scene/Scene.hpp>
#include <Strake/Component/Script.hpp>
#include <Strake/Component/Transform.hpp>

namespace Strake {

    GameObject::GameObject(std::string name, EventDispatcher &eventDispatcher, Layer &layer) :
        m_name(std::move(name)),
        m_eventDispatcher(eventDispatcher),
        r_layer(layer)
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
        m_children[name] = std::make_unique<GameObject>(name, m_eventDispatcher, r_layer);
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
        int oldLayer = r_layer.get().getPriority();
        std::pair<std::string, GameObject &> pair = {name, *this};
        EventData<std::pair<std::string, GameObject &>> eventData(pair, "setLayerByName");
        m_eventDispatcher.broadcast(eventData);
        updateLayers(oldLayer);
    }

    void GameObject::setLayer(int priority) {
        int oldLayer = r_layer.get().getPriority();
        std::pair<int, GameObject &> pair = {priority, *this};
        EventData<std::pair<int, GameObject &>> eventData(pair, "setLayerByPriority");
        m_eventDispatcher.broadcast(eventData);
        updateLayers(oldLayer);
    }

    void GameObject::setLayer(Layer &layer, bool update) {
        int oldLayer = r_layer.get().getPriority();
        r_layer = layer;
        if (update) {
            updateLayers(oldLayer);
        }
    }

    void GameObject::updateLayers(int oldLayer) {
        std::optional<std::reference_wrapper<Renderer>> renderer = findComponent<Renderer>();
        std::optional<std::reference_wrapper<Light>> light = findComponent<Light>();
        if (renderer.has_value()) {
            renderer.value().get().updateLayer(oldLayer);
        }
        if (light.has_value()) {
            light.value().get().updateLayer(oldLayer);
        }
    }

    Layer &GameObject::getLayer() const {
        return r_layer.get();
    }
}