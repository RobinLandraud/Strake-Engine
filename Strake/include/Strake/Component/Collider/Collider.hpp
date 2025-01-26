#pragma once

#include <Strake/Component/Component.hpp>
#include <Strake/Component/Transform.hpp>
#include <Strake/Dispatcher/EventData.hpp>

namespace Strake {
    enum ColliderType {
        None,
        OBB,
        AABB,
        Sphere,
        Mesh
    };

    enum CollisionMode {
        Discrete,
        Continuous
    };

    class Collider : public Component
    {
        public:
            Collider(GameObject &parent, ColliderType type, CollisionMode mode);
            explicit Collider(GameObject &parent, ColliderType type); // is Discrete by default
            ~Collider();

            virtual void physicsUpdate() = 0;
            [[nodiscard]] virtual bool isColliding(Collider &other) const = 0;
            
            [[nodiscard]] ColliderType getType() const;
            [[nodiscard]] CollisionMode getMode() const;

        protected:
            Transform &r_transform;
            ColliderType m_type;
            CollisionMode m_mode;
    };
}