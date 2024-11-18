#include <ECS/MeshFilter.hpp>

namespace ECS
{
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

    void MeshFilter::loadFromOBJ(const std::string &path)
    {
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