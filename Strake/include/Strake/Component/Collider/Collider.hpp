#pragma once

#include <Strake/Component/Component.hpp>
#include <Strake/Component/Transform.hpp>
#include <Strake/Component/MeshFilter/MeshFilter.hpp>
#include <Strake/Dispatcher/EventData.hpp>
#include <Strake/Shader/ShaderProgram.hpp>

namespace Strake {
    enum ColliderType {
        None,
        OBB,
        AABB,
        CSphere,
        Mesh
    };

    enum CollisionMode {
        Discrete,
        Continuous
    };

    class Collider : public Component
    {
        public:
            Collider(GameObject &parent, ColliderType type, CollisionMode mode, glm::vec3 offset = glm::vec3(0.0f));
            explicit Collider(GameObject &parent, ColliderType type); // is Discrete by default
            ~Collider();

            virtual void physicsUpdate() = 0;
            [[nodiscard]] virtual bool isColliding(Collider &other) const = 0;
            
            [[nodiscard]] ColliderType getType() const;
            [[nodiscard]] CollisionMode getMode() const;

            [[nodiscard]] bool hasMesh() const;
            [[nodiscard]] MeshFilter &getMesh();

            [[nodiscard]] const glm::vec3 &getMeshCenter() const;

        protected:
            Transform &r_transform;
            glm::vec3 m_meshCenter;
            ColliderType m_type;
            CollisionMode m_mode;

            //used if debug is enabled
            std::optional<MeshFilter> m_mesh;
    };
}