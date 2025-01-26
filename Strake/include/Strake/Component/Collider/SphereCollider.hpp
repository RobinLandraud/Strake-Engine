#pragma once

#include <Strake/Component/Collider/Collider.hpp>
#include <Strake/Component/MeshFilter/MeshFilter.hpp>

namespace Strake {
    class SphereCollider : public Collider
    {
        public:
            explicit SphereCollider(GameObject &parent);
            ~SphereCollider() = default;

            virtual void physicsUpdate() final;

            [[nodiscard]] bool isColliding(Collider &other) const override;

        private:
            glm::vec3 meshCenter; // static (center of mesh retated to position 0,0,0 of mesh)
            glm::vec3 center;
            float meshRadius; // static (radius of mesh)
            float radius; // dynamic (radius of mesh changing with world scale)
    };
}