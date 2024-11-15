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
    void Component::render() {}

    GameObject &Component::getParent() const {
        return r_parent;
    }
}