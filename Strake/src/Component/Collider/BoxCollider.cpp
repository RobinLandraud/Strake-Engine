#include <Strake/Component/Collider/BoxCollider.hpp>

namespace Strake {
    BoxCollider::BoxCollider(GameObject &parent) :
        Collider(parent, ColliderType::OBB)
    {
        std::optional<std::reference_wrapper<MeshFilter>> meshFilter = parent.findComponent<MeshFilter>();
        if (!meshFilter.has_value()) {
            throw std::runtime_error("BoxCollider requires a MeshFilter component");
        }
        std::vector<glm::vec3> r_vertices = meshFilter.value().get().getVertices();

        // get the center of the mesh
        for (const glm::vec3 &vertex : r_vertices) {
            meshCenter += vertex;
        }
        meshCenter /= r_vertices.size();
        center = r_transform.getWorldPosition() + meshCenter;
        rotation = r_transform.getWorldRotation();

        // get the half size of the mesh (with meshCenter as the center)
        for (const glm::vec3 &vertex : r_vertices) {
            if (vertex.x < meshCenter.x - halfSize.x) {
                halfSize.x = meshCenter.x - vertex.x;
            }
            if (vertex.x > meshCenter.x + halfSize.x) {
                halfSize.x = vertex.x - meshCenter.x;
            }
            if (vertex.y < meshCenter.y - halfSize.y) {
                halfSize.y = meshCenter.y - vertex.y;
            }
            if (vertex.y > meshCenter.y + halfSize.y) {
                halfSize.y = vertex.y - meshCenter.y;
            }
            if (vertex.z < meshCenter.z - halfSize.z) {
                halfSize.z = meshCenter.z - vertex.z;
            }
            if (vertex.z > meshCenter.z + halfSize.z) {
                halfSize.z = vertex.z - meshCenter.z;
            }
            meshCenter += vertex;
        }
    }

    BoxCollider::BoxCollider(GameObject &parent, BoxColliderType type) :
        Collider(parent, ColliderType::OBB, CollisionMode::Discrete)
    {

    }

    void BoxCollider::physicsUpdate()
    {
        center = r_transform.getWorldPosition() + meshCenter;
        rotation = r_transform.getWorldRotation();
    }

    bool BoxCollider::isColliding(Collider &other) const
    {
        switch (other.getType()) {
            case ColliderType::OBB:
                break;
            default:
                break;
        }
        return false;
    }
}