#pragma once

#include <ECS/Component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ECS
{
    class MeshFilter : public Component
    {
        public:
            MeshFilter(GameObject &parent);

            void setVertices(const std::vector<glm::vec3> &vertices);
            void setNormals(const std::vector<glm::vec3> &normals);
            void setUVs(const std::vector<glm::vec2> &uvs);
            void setIndices(const std::vector<unsigned int> &indices);

            [[nodiscard]] const std::vector<glm::vec3> &getVertices() const;
            [[nodiscard]] const std::vector<glm::vec3> &getNormals() const;
            [[nodiscard]] const std::vector<glm::vec2> &getUVs() const;
            [[nodiscard]] const std::vector<unsigned int> &getIndices() const;

            void loadFromOBJ(const std::string &path);

            [[nodiscard]] bool isUpdated() const;
            void setUpdated(bool updated);

        private:
            bool m_isUpdated = false;
            std::vector<glm::vec3> m_vertices;
            std::vector<glm::vec3> m_normals;
            std::vector<glm::vec2> m_uvs;
            std::vector<unsigned int> m_indices;
    };
}