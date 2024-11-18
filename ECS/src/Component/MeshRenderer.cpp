#include <ECS/MeshRenderer.hpp>

namespace ECS {
    MeshRenderer::MeshRenderer(GameObject &parent, MeshFilter &meshFilter, Material &material) :
        Component(parent),
        m_meshFilter(meshFilter),
        m_material(material),
        m_VAO(0),
        m_VBO(0),
        m_EBO(0)
    {
        setupMesh();
    }

    MeshRenderer::MeshRenderer(GameObject &parent, Material &material) :
        Component(parent),
        m_meshFilter(parent.getComponent<MeshFilter>()),
        m_material(material),
        m_VAO(0),
        m_VBO(0),
        m_EBO(0)
    {
        setupMesh();
    }

    MeshRenderer::~MeshRenderer()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    void MeshRenderer::setupMesh()
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        // Combine vertex positions and texture coordinates into a single buffer
        std::vector<float> vertexData;
        const auto& vertices = m_meshFilter.getVertices();
        const auto& uvs = m_meshFilter.getUVs();
        vertexData.reserve(vertices.size() * 5); // 3 for position + 2 for texture coordinates

        for (size_t i = 0; i < vertices.size(); ++i) {
            vertexData.push_back(vertices[i].x);
            vertexData.push_back(vertices[i].y);
            vertexData.push_back(vertices[i].z);
            vertexData.push_back(uvs[i].x);
            vertexData.push_back(uvs[i].y);
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshFilter.getIndices().size() * sizeof(unsigned int), m_meshFilter.getIndices().data(), GL_STATIC_DRAW);

        // Vertex positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture coordinates
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_meshFilter.setUpdated(false);
    }

    void MeshRenderer::render(Camera &camera)
    {
        m_material.bind();

        m_material.getShaderProgram().setUniform("model", getParent().getComponent<Transform>().getMatrix());
        if (camera.hasChangedView()) {
            m_material.getShaderProgram().setUniform("view", camera.getViewMatrix());
        }
        if (camera.hasChangedProjection()) {
            m_material.getShaderProgram().setUniform("projection", camera.getProjectionMatrix());
        }
        camera.resetUpdateFlags();
        
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_meshFilter.getIndices().size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        m_material.unbind();
    }

    void MeshRenderer::lateUpdate()
    {
        if (!m_meshFilter.isUpdated()) {
            return;
        }
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_meshFilter.getVertices().size() * sizeof(glm::vec3), m_meshFilter.getVertices().data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_meshFilter.getIndices().size() * sizeof(unsigned int), m_meshFilter.getIndices().data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        m_meshFilter.setUpdated(false);
    }

    const MeshFilter &MeshRenderer::getMeshFilter() const
    {
        return m_meshFilter;
    }

    const Material &MeshRenderer::getMaterial() const
    {
        return m_material;
    }
}