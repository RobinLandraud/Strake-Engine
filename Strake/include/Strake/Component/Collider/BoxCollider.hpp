#pragma once

#include <Strake/Component/Collider/Collider.hpp>
#include <Strake/Component/MeshFilter/MeshFilter.hpp>

namespace Strake {
    enum class BoxColliderType {
        AABB,
        OBB
    };

    class BoxCollider : public Collider
    {
        public:
            explicit BoxCollider(GameObject &parent); // is OBB by default
            BoxCollider(GameObject &parent, BoxColliderType type);
            ~BoxCollider() = default;

            virtual void physicsUpdate() final;

            [[nodiscard]] bool isColliding(Collider &other) const override;

        private:
            BoxColliderType m_boxType;

            glm::vec3 meshCenter; // static
            glm::vec3 center;
            glm::vec3 halfSize;
            glm::vec3 rotation; // only for OBB
    };
}