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
        for (const glm::vec3 &vertex : r_vertices) {
            if (vertex.x < meshCenterOffset.x - halfSize.x) {
                halfSize.x = meshCenterOffset.x - vertex.x;
            }
            if (vertex.x > meshCenterOffset.x + halfSize.x) {
                halfSize.x = vertex.x - meshCenterOffset.x;
            }
            if (vertex.y < meshCenterOffset.y - halfSize.y) {
                halfSize.y = meshCenterOffset.y - vertex.y;
            }
            if (vertex.y > meshCenterOffset.y + halfSize.y) {
                halfSize.y = vertex.y - meshCenterOffset.y;
            }
            if (vertex.z < meshCenterOffset.z - halfSize.z) {
                halfSize.z = meshCenterOffset.z - vertex.z;
            }
            if (vertex.z > meshCenterOffset.z + halfSize.z) {
                halfSize.z = vertex.z - meshCenterOffset.z;
            }
            meshCenterOffset += vertex;
        }
        meshCenterOffset /= r_vertices.size();
        center = r_transform.getWorldPosition() + meshCenterOffset;
        rotation = r_transform.getWorldRotation();
    }

    BoxCollider::BoxCollider(GameObject &parent, BoxColliderType type) :
        Collider(parent, ColliderType::OBB, CollisionMode::Discrete)
    {

    }

    void BoxCollider::physicsUpdate()
    {
        center = r_transform.getWorldPosition() + meshCenterOffset;
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