#include <ECS/Component.hpp>

namespace ECS {
    Component::Component(
        GameObject &parent
        )
        : r_parent(parent)
    {
    }

    void Component::awake() {}
    void Component::start() {}
    void Component::update() {}
    void Component::fixedUpdate() {}
    void Component::lateUpdate() {}
    void Component::render(Camera &camera) {}

    void Component::setDerivedType(const std::type_index &type) {
        m_derivedType = type;
    }

    std::type_index Component::getDerivedType() const {
        return m_derivedType;
    }

    GameObject &Component::getParent() const {
        return r_parent;
    }
}