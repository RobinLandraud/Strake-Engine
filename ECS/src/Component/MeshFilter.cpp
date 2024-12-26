#include <ECS/MeshFilter.hpp>
#include <iostream>

namespace ECS
{
    struct PackedVertex {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;

        bool operator<(const PackedVertex& other) const {
            return memcmp((void*)this, (void*)&other, sizeof(PackedVertex)) > 0;
        }
    };

    MeshFilter::MeshFilter(GameObject &parent) : Component(parent)
    {
        setDerivedType(typeid(MeshFilter));
    }

    MeshFilter::MeshFilter(const MeshFilter &other) : Component(other)
    {
        m_vertices = other.m_vertices;
        m_normals = other.m_normals;
        m_uvs = other.m_uvs;
        m_indices = other.m_indices;
        m_isUpdated = true;
    }

    MeshFilter &MeshFilter::operator=(const MeshFilter &other)
    {
        if (this == &other) {
            return *this;
        }

        m_vertices = other.m_vertices;
        m_normals = other.m_normals;
        m_uvs = other.m_uvs;
        m_indices = other.m_indices;
        m_isUpdated = true;

        return *this;
    }

    void MeshFilter::setVertices(const std::vector<glm::vec3> &vertices)
    {
        m_vertices = vertices;
        m_isUpdated = true;
    }

    void MeshFilter::setNormals(const std::vector<glm::vec3> &normals)
    {
        m_normals = normals;
        m_isUpdated = true;
    }

    void MeshFilter::setUVs(const std::vector<glm::vec2> &uvs)
    {
        m_uvs = uvs;
        m_isUpdated = true;
    }

    void MeshFilter::setIndices(const std::vector<unsigned int> &indices)
    {
        m_indices = indices;
        m_isUpdated = true;
    }

    const std::vector<glm::vec3> &MeshFilter::getVertices() const
    {
        return m_vertices;
    }

    const std::vector<glm::vec3> &MeshFilter::getNormals() const
    {
        return m_normals;
    }

    const std::vector<glm::vec2> &MeshFilter::getUVs() const
    {
        return m_uvs;
    }

    const std::vector<unsigned int> &MeshFilter::getIndices() const
    {
        return m_indices;
    }

    void ECS::MeshFilter::loadFromFile(const std::string &path, short index) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw std::runtime_error("Failed to load mesh file: " + path);
            return;
        }

        if (scene->mNumMeshes == 0) {
            throw std::runtime_error("No meshes found in file: " + path);
            return;
        }

        aiMesh* mesh = scene->mMeshes[index];
        m_vertices.clear();
        m_normals.clear();
        m_uvs.clear();
        m_indices.clear();

        // Extract vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            m_vertices.emplace_back(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

            if (mesh->HasNormals()) {
                m_normals.emplace_back(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            }

            if (mesh->HasTextureCoords(0)) {
                m_uvs.emplace_back(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
        }

        // Extract indices
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j) {
                m_indices.push_back(face.mIndices[j]);
            }
        }

        m_isUpdated = true; // Mark the mesh as updated
    }

    void ECS::MeshFilter::loadFromFile(const std::string &path)
    {
        loadFromFile(path, 0);
    }


    void MeshFilter::setUpdated(bool updated)
    {
        m_isUpdated = updated;
    }

    bool MeshFilter::isUpdated() const
    {
        return m_isUpdated;
    }
}