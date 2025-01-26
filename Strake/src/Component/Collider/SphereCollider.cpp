#include <Strake/Component/Collider/SphereCollider.hpp>

namespace Strake {
    SphereCollider::SphereCollider(GameObject &parent) :
        Collider(parent, ColliderType::CSphere),
        m_center(0.0f),
        m_meshRadius(0.0f),
        m_radius(0.0f)
    {
        std::optional<std::reference_wrapper<MeshFilter>> meshFilter = parent.findComponent<MeshFilter>();
        if (!meshFilter.has_value()) {
            throw std::runtime_error("SphereCollider requires a MeshFilter component");
        }
        std::vector<glm::vec3> r_vertices = meshFilter.value().get().getVertices();

        // get the center of the mesh
        for (const glm::vec3 &vertex : r_vertices) {
            m_meshCenter += vertex;
        }
        m_meshCenter /= r_vertices.size();

        // get the m_meshRadius of the mesh (with m_meshCenter as the center)
        m_meshRadius = 0.0f;
        for (const glm::vec3 &vertex : r_vertices) {
            float distance = glm::distance(vertex, m_meshCenter);
            if (distance > m_meshRadius) {
                m_meshRadius = distance;
            }
        }

        physicsUpdate();

        m_mesh = Sphere(getParent(), m_meshRadius);
    }

    void SphereCollider::physicsUpdate()
    {
        glm::vec4 localCenter = glm::vec4(m_meshCenter, 1.0f);        // Homogeneous coordinates
        glm::vec4 worldCenter = r_transform.getWorldMatrix() * localCenter;            // Transform to world space
        m_center = glm::vec3(worldCenter);                            // Extract the 3D position
    }

    bool SphereCollider::isColliding(Collider &other) const
    {
        switch (other.getType()) {
            case ColliderType::CSphere: {
                SphereCollider &sphere = static_cast<SphereCollider&>(other);
                float distance = glm::distance(m_center, sphere.m_center);
                std::cout << distance << std::endl;
                return distance < m_radius + sphere.m_radius;
            }
            default:
                break;
        }
        return false;
    }
}