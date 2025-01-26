#pragma once

#include <Strake/Component/Collider/Collider.hpp>
#include <Strake/Component/MeshFilter/Sphere.hpp>

namespace Strake {
    class SphereCollider : public Collider
    {
        public:
            explicit SphereCollider(GameObject &parent);
            ~SphereCollider() = default;

            virtual void physicsUpdate() final;

            [[nodiscard]] bool isColliding(Collider &other) const override;

        private:
            glm::vec3 m_center; // world (center of mesh)
            float m_meshRadius; // static (radius of mesh)
            float m_radius; // dynamic (radius of mesh changing with world scale)
    };
}