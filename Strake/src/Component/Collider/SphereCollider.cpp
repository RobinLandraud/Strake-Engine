#include <Strake/Component/Collider/SphereCollider.hpp>

namespace Strake {
    SphereCollider::SphereCollider(GameObject &parent) :
        Collider(parent, ColliderType::Sphere)
    {
        std::optional<std::reference_wrapper<MeshFilter>> meshFilter = parent.findComponent<MeshFilter>();
        if (!meshFilter.has_value()) {
            throw std::runtime_error("SphereCollider requires a MeshFilter component");
        }
        std::vector<glm::vec3> r_vertices = meshFilter.value().get().getVertices();

        // get the center of the mesh
        for (const glm::vec3 &vertex : r_vertices) {
            meshCenter += vertex;
        }
        meshCenter /= r_vertices.size();

        // get the meshRadius of the mesh (with meshCenter as the center)
        meshRadius = 0.0f;
        for (const glm::vec3 &vertex : r_vertices) {
            float distance = glm::distance(vertex, meshCenter);
            if (distance > meshRadius) {
                meshRadius = distance;
            }
        }

        physicsUpdate();
    }

    void SphereCollider::physicsUpdate()
    {
        glm::vec4 localCenter = glm::vec4(meshCenter, 1.0f);        // Homogeneous coordinates
        glm::vec4 worldCenter = r_transform.getWorldMatrix() * localCenter;            // Transform to world space
        center = glm::vec3(worldCenter);                            // Extract the 3D position
    }

    bool SphereCollider::isColliding(Collider &other) const
    {
        switch (other.getType()) {
            case ColliderType::Sphere: {
                SphereCollider &sphere = static_cast<SphereCollider&>(other);
                float distance = glm::distance(center, sphere.center);
                std::cout << distance << std::endl;
                return distance < radius + sphere.radius;
            }
            default:
                break;
        }
        return false;
    }
}