#include <Strake/Component/Collider/Collider.hpp>

namespace Strake {
    Collider::Collider(GameObject &parent, ColliderType type, CollisionMode mode) :
        Component(parent),
        r_transform(parent.getTransform()),
        m_meshCenter(0.0f),
        m_type(type),
        m_mode(mode),
        m_mesh(std::nullopt)
    {
        setDerivedType(typeid(Collider));
        EventData<Collider> eventData(*this, "addCollider");
        parent.getEventDispatcher().broadcast(eventData);
    }

    Collider::~Collider() {
        EventData<Collider> eventData(*this, "removeCollider");
        getParent().getEventDispatcher().broadcast(eventData);
    }

    Collider::Collider(GameObject &parent, ColliderType type) :
        Collider(parent, type, CollisionMode::Discrete)
    {
    }

    ColliderType Collider::getType() const {
        return m_type;
    }

    CollisionMode Collider::getMode() const {
        return m_mode;
    }

    bool Collider::hasMesh() const {
        return m_mesh.has_value();
    }

    MeshFilter &Collider::getMesh() {
        if (!m_mesh.has_value()) {
            throw std::runtime_error("Collider has no mesh");
        }
        return m_mesh.value();
    }

    const glm::vec3 &Collider::getMeshCenter() const {
        return m_meshCenter;
    }
}