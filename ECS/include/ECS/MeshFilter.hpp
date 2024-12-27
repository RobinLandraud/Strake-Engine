#pragma once

#define _CRT_SECURE_NO_WARNINGS // for fopen, fscanf, etc.

#include <ECS/Component.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>
#include <map>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace ECS
{
    class MeshFilter : public Component
    {
        public:
            MeshFilter(GameObject &parent);

            MeshFilter(const MeshFilter &other);
            MeshFilter &operator=(const MeshFilter &other);

            void setVertices(const std::vector<glm::vec3> &vertices);
            void setNormals(const std::vector<glm::vec3> &normals);
            void setUVs(const std::vector<glm::vec2> &uvs);
            void setIndices(const std::vector<unsigned int> &indices);

            [[nodiscard]] const std::vector<glm::vec3> &getVertices() const;
            [[nodiscard]] const std::vector<glm::vec3> &getNormals() const;
            [[nodiscard]] const std::vector<glm::vec2> &getUVs() const;
            [[nodiscard]] const std::vector<unsigned int> &getIndices() const;

            std::vector<std::reference_wrapper<ECS::GameObject>> loadFromFile(const std::string &path);
            void loadFromFile(const std::string &path, unsigned int index);

            [[nodiscard]] bool isUpdated() const;
            void setUpdated(bool updated);

        protected:
            bool m_isUpdated = false;
            std::vector<glm::vec3> m_vertices;
            std::vector<glm::vec3> m_normals;
            std::vector<glm::vec2> m_uvs;
            std::vector<unsigned int> m_indices;
    };

    class Cube : public MeshFilter
    {
        public:
            Cube(GameObject &parent);
    };
}