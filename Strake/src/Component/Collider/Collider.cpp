#include <Strake/Component/Collider/Collider.hpp>

namespace Strake {
    Collider::Collider(GameObject &parent, ColliderType type, CollisionMode mode) :
        Component(parent),
        r_transform(parent.getTransform()),
        m_type(type),
        m_mode(mode)
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
}