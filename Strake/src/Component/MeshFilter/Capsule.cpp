#include <Strake/Component/MeshFilter/Capsule.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>     // pour glm::pi<float>()
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <vector>

namespace Strake {
    Capsule::Capsule(GameObject &parent, float radius, float height, int sectorCount, int stackCount)
        : MeshFilter(parent),
        m_sectorCount(sectorCount),
        m_stackCount(stackCount),
        m_radius(radius),
        m_height(height)
    {
        // Pour la capsule, la partie cylindrique s’étend de -halfHeight à +halfHeight
        float halfHeight = m_height / 2.0f;

        //
        // 1. Génération des vertices et normales
        //

        // --- Dôme supérieur (hémisphère haut) ---
        // On paramètre avec phi allant de 0 (pôle supérieur) à π/2 (équateur)
        for (int i = 0; i <= m_stackCount; ++i)
        {
            // phi varie de 0 à π/2
            float phi = (glm::pi<float>() / 2) * (float(i) / m_stackCount);
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            for (int j = 0; j <= m_sectorCount; ++j)
            {
                // theta parcourt 0 à 2π
                float theta = 2 * glm::pi<float>() * float(j) / m_sectorCount;
                float sinTheta = sin(theta);
                float cosTheta = cos(theta);

                // Position sur la sphère centrée en (0, halfHeight, 0)
                float x = m_radius * sinPhi * cosTheta;
                float y = halfHeight + m_radius * cosPhi;
                float z = m_radius * sinPhi * sinTheta;
                m_vertices.emplace_back(x, y, z);

                // La normale est celle d'une sphère (vector de (vertex - centre))
                glm::vec3 normal = glm::normalize(glm::vec3(x, m_radius * cosPhi, z));
                // Autrement dit, puisque le centre est (0, halfHeight, 0) :
                normal = glm::normalize(glm::vec3(x, y - halfHeight, z));
                m_normals.emplace_back(normal);

                // UV simples : u selon theta, v selon phi
                float u = float(j) / m_sectorCount;
                float v = float(i) / m_stackCount;
                m_uvs.emplace_back(u, v);
            }
        }

        // --- Dôme inférieur (hémisphère bas) ---
        // Ici, phi varie de 0 (équateur) à π/2 (pôle inférieur)
        for (int i = 0; i <= m_stackCount; ++i)
        {
            float phi = (glm::pi<float>() / 2) * (float(i) / m_stackCount);
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            for (int j = 0; j <= m_sectorCount; ++j)
            {
                float theta = 2 * glm::pi<float>() * float(j) / m_sectorCount;
                float sinTheta = sin(theta);
                float cosTheta = cos(theta);

                // Position sur la sphère centrée en (0, -halfHeight, 0)
                float x = m_radius * sinPhi * cosTheta;
                float y = -halfHeight - m_radius * cosPhi;
                float z = m_radius * sinPhi * sinTheta;
                m_vertices.emplace_back(x, y, z);

                // Normale (vertex - centre)
                glm::vec3 normal = glm::normalize(glm::vec3(x, y + halfHeight, z));
                m_normals.emplace_back(normal);

                float u = float(j) / m_sectorCount;
                float v = float(i) / m_stackCount;
                m_uvs.emplace_back(u, v);
            }
        }

        // --- Partie cylindrique ---
        // On génère des anneaux du cercle en Y variant de -halfHeight à +halfHeight
        for (int i = 0; i <= m_stackCount; ++i)
        {
            // y varie linéairement le long du cylindre
            float y = -halfHeight + i * (m_height / float(m_stackCount));
            for (int j = 0; j <= m_sectorCount; ++j)
            {
                float theta = 2 * glm::pi<float>() * float(j) / m_sectorCount;
                float cosTheta = cos(theta);
                float sinTheta = sin(theta);
                float x = m_radius * cosTheta;
                float z = m_radius * sinTheta;
                m_vertices.emplace_back(x, y, z);
                // La normale pointe radialement (en XZ)
                m_normals.emplace_back(glm::vec3(cosTheta, 0.0f, sinTheta));

                float u = float(j) / m_sectorCount;
                float v = float(i) / m_stackCount;
                m_uvs.emplace_back(u, v);
            }
        }

        //
        // 2. Génération des indices
        //
        // Nous savons que :
        // - Les vertices du dôme supérieur occupent les indices [0, topCount-1]
        //   avec topCount = (m_stackCount+1) * (m_sectorCount+1)
        // - Ceux du dôme inférieur occupent ensuite les indices [topCount, topCount+bottomCount-1]
        //   avec bottomCount = (m_stackCount+1) * (m_sectorCount+1)
        // - Et la partie cylindrique occupe la suite.
        //
        int topOffset = 0;
        int topRows = m_stackCount + 1; // nombre de lignes dans le dôme supérieur
        int topCount = topRows * (m_sectorCount + 1);

        int bottomOffset = topCount;
        int bottomRows = m_stackCount + 1; // pour le dôme inférieur
        int bottomCount = bottomRows * (m_sectorCount + 1);

        int cylinderOffset = bottomOffset + bottomCount;
        int cylinderRows = m_stackCount + 1; // pour le cylindre

        // --- Indices pour le dôme supérieur ---
        // On parcourt la grille (sauf la première ligne si celle‑ci est dégénérée)
        for (int i = 1; i < topRows; ++i)
        {
            int k1 = topOffset + (i - 1) * (m_sectorCount + 1); // ligne précédente
            int k2 = topOffset + i * (m_sectorCount + 1);         // ligne courante

            for (int j = 0; j < m_sectorCount; ++j, ++k1, ++k2)
            {
                // Pour la première ligne (proche du pôle), on forme des triangles en éventail
                if (i == 1)
                {
                    m_indices.push_back(k1);
                    m_indices.push_back(k2 + 1);
                    m_indices.push_back(k2);
                }
                else
                {
                    // Deux triangles par quad
                    m_indices.push_back(k1);
                    m_indices.push_back(k1 + 1);
                    m_indices.push_back(k2);

                    m_indices.push_back(k1 + 1);
                    m_indices.push_back(k2 + 1);
                    m_indices.push_back(k2);
                }
            }
        }

        // --- Indices pour le dôme inférieur ---
        for (int i = 1; i < bottomRows; ++i)
        {
            int k1 = bottomOffset + (i - 1) * (m_sectorCount + 1);
            int k2 = bottomOffset + i * (m_sectorCount + 1);
            for (int j = 0; j < m_sectorCount; ++j, ++k1, ++k2)
            {
                if (i == 1)
                {
                    m_indices.push_back(k1);
                    m_indices.push_back(k2);
                    m_indices.push_back(k2 + 1);
                }
                else
                {
                    m_indices.push_back(k1 + 1);
                    m_indices.push_back(k1);
                    m_indices.push_back(k2);

                    m_indices.push_back(k1 + 1);
                    m_indices.push_back(k2);
                    m_indices.push_back(k2 + 1);
                }
            }
        }

        // --- Indices pour la partie cylindrique ---
        for (int i = 0; i < cylinderRows - 1; ++i)
        {
            int k1 = cylinderOffset + i * (m_sectorCount + 1);
            int k2 = cylinderOffset + (i + 1) * (m_sectorCount + 1);
            for (int j = 0; j < m_sectorCount; ++j, ++k1, ++k2)
            {
                m_indices.push_back(k1);
                m_indices.push_back(k2);
                m_indices.push_back(k1 + 1);

                m_indices.push_back(k1 + 1);
                m_indices.push_back(k2);
                m_indices.push_back(k2 + 1);
            }
        }
    }
} // namespace Strake
