#include <Strake/Component/Renderer/WireFrameRenderer.hpp>

namespace Strake {
    WireFrameRenderer::WireFrameRenderer(GameObject &parent, MeshFilter &mesh, glm::vec3 offset) :
        Renderer(parent, RendererType::WireFrameRenderer),
        r_mesh(mesh),
        m_offset(offset),
        m_lineWidth(1.0f),
        m_lineColor(1.0f, 1.0f, 1.0f),
        m_shaderProgram(
            std::string(RESOURCES_PATH) + "/Shaders/wireframe/vertex.glsl",
            std::string(RESOURCES_PATH) + "/Shaders/wireframe/fragment.glsl"
        )
    {
        setDerivedType(typeid(WireFrameRenderer));
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        m_shaderProgram.use();
        m_shaderProgram.setUniform("lineColor", m_lineColor);
        setupMesh();
    }

    WireFrameRenderer::WireFrameRenderer(GameObject &parent, Collider &collider) :
        WireFrameRenderer(parent, collider.getMesh(), collider.getMeshCenter())
    {
    }

    WireFrameRenderer::~WireFrameRenderer()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    void WireFrameRenderer::setupMesh()
    {
        const auto& vertices = r_mesh.getVertices();
        const auto& uvs = r_mesh.getUVs();
        const auto& normals = r_mesh.getNormals();

        // Validate data
        if (vertices.empty() || vertices.size() != uvs.size() || vertices.size() != normals.size()) {
            throw std::runtime_error("Invalid mesh data");
        }

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        std::vector<float> vertexData;
        vertexData.reserve(vertices.size() * 8);

        for (size_t i = 0; i < vertices.size(); ++i) {
            vertexData.push_back(vertices[i].x);
            vertexData.push_back(vertices[i].y);
            vertexData.push_back(vertices[i].z);
            vertexData.push_back(uvs[i].x);
            vertexData.push_back(uvs[i].y);
            vertexData.push_back(normals[i].x);
            vertexData.push_back(normals[i].y);
            vertexData.push_back(normals[i].z);
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

        const auto& indices = r_mesh.getIndices();
        if (indices.empty()) {
            throw std::runtime_error("No indices provided");
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Vertex positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture coordinates
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Normals
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        r_mesh.setUpdated(false);
    }

    void WireFrameRenderer::GLrender()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(m_lineWidth);
        glBindVertexArray(m_VAO);
        glDrawElements(GL_LINES, static_cast<GLsizei>(r_mesh.getIndices().size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void WireFrameRenderer::render(Camera &camera)
    {
        m_shaderProgram.use();
        m_shaderProgram.setUniform("model", glm::translate(getParent().getTransform().getWorldMatrix(), m_offset));
        m_shaderProgram.setUniform("view", camera.getViewMatrix());
        m_shaderProgram.setUniform("projection", camera.getProjectionMatrix());
        camera.resetUpdateFlags();
        GLrender();
    }

    void WireFrameRenderer::setLineWidth(float lineWidth)
    {
        m_lineWidth = lineWidth;
    }

    void WireFrameRenderer::setLineColor(const glm::vec3 &lineColor)
    {
        m_lineColor = lineColor;
        m_shaderProgram.use();
        m_shaderProgram.setUniform("lineColor", m_lineColor);
    }

    float WireFrameRenderer::getLineWidth() const
    {
        return m_lineWidth;
    }

    const glm::vec3 &WireFrameRenderer::getLineColor() const
    {
        return m_lineColor;
    }
}