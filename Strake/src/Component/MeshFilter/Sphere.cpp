#include <Strake/Component/MeshFilter/Sphere.hpp>
#include <cmath>

namespace Strake {
    Sphere::Sphere(GameObject &parent, float radius, int sectorCount, int stackCount)
        : MeshFilter(parent),
        m_sectorCount(sectorCount),
        m_stackCount(stackCount),
        m_radius(radius)
    {
        for (int i = 0; i <= m_stackCount; ++i) {
            float stackAngle = glm::pi<float>() / 2 - i * glm::pi<float>() / m_stackCount; // from pi/2 to -pi/2
            float xy = m_radius * cosf(stackAngle); // m_radius at current stack
            float z = m_radius * sinf(stackAngle); // z coordinate

            for (int j = 0; j <= m_sectorCount; ++j) {
                float sectorAngle = j * 2 * glm::pi<float>() / m_sectorCount; // from 0 to 2pi
                float x = xy * cosf(sectorAngle); // x coordinate
                float y = xy * sinf(sectorAngle); // y coordinate

                m_vertices.emplace_back(x, y, z);
                m_normals.emplace_back(x, y, z);
                m_uvs.emplace_back(static_cast<float>(j) / m_sectorCount, static_cast<float>(i) / m_stackCount);
            }
        }

        // Indices
        for (int i = 0; i < m_stackCount; ++i) {
            int k1 = i * (m_sectorCount + 1); // current stack
            int k2 = k1 + m_sectorCount + 1;  // next stack

            for (int j = 0; j < m_sectorCount; ++j, ++k1, ++k2) {
                if (i != 0) {
                    m_indices.push_back(k1);
                    m_indices.push_back(k2);
                    m_indices.push_back(k1 + 1);
                }

                if (i != (m_stackCount - 1)) {
                    m_indices.push_back(k2);
                    m_indices.push_back(k2 + 1);
                    m_indices.push_back(k1 + 1);
                }
            }
        }
    }
}