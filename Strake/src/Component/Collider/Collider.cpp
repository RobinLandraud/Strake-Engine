#include <Strake/Component/Collider/Collider.hpp>

namespace Strake {
    Collider::Collider(GameObject &parent, ColliderType type, CollisionMode mode) :
        Component(parent),
        r_transform(parent.getTransform()),
        m_type(type),
        m_mode(mode)
    {
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