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
        setDerivedType(typeid(MeshRenderer));
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
        setDerivedType(typeid(MeshRenderer));
    }

    MeshRenderer::~MeshRenderer()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    void MeshRenderer::setupMesh()
    {
        const auto& vertices = m_meshFilter.getVertices();
        const auto& uvs = m_meshFilter.getUVs();
        const auto& normals = m_meshFilter.getNormals();

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

        const auto& indices = m_meshFilter.getIndices();
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

        m_meshFilter.setUpdated(false);
    }

    void MeshRenderer::render(Camera &camera)
    {
        m_material.bind();

        m_material.getShaderProgram().setUniform("model", getParent().getComponent<Transform>().getWorldMatrix());
        m_material.getShaderProgram().setUniform("view", camera.getViewMatrix());
        m_material.getShaderProgram().setUniform("viewPos", camera.getPosition());
        m_material.getShaderProgram().setUniform("projection", camera.getProjectionMatrix());
        camera.resetUpdateFlags();

        std::cout << "DEBUG:" << std::endl;
        std::cout << "Rendering object: " << getParent().getName() << std::endl;
        std::cout << "Rendering object: " << getParent().getName() << std::endl;
        std::cout << "light.position: " << m_material.getShaderProgram().getUniformVec3("light.position").x << " " << m_material.getShaderProgram().getUniformVec3("light.position").y << " " << m_material.getShaderProgram().getUniformVec3("light.position").z << std::endl;
        std::cout << "light.color: " << m_material.getShaderProgram().getUniformVec3("light.color").x << " " << m_material.getShaderProgram().getUniformVec3("light.color").y << " " << m_material.getShaderProgram().getUniformVec3("light.color").z << std::endl;
        std::cout << "light.intensity: " << m_material.getShaderProgram().getUniformFloat("light.intensity") << std::endl;
        std::cout << "textureSampler: " << m_material.getShaderProgram().getUniformInt("textureSampler") << std::endl;
        std::cout << "alphaThreshold: " << m_material.getShaderProgram().getUniformFloat("alphaThreshold") << std::endl;
        std::cout << "shiniess: " << m_material.getShaderProgram().getUniformFloat("shininess") << std::endl;
        std::cout << "ambientIntensity: " << m_material.getShaderProgram().getUniformFloat("ambientIntensity") << std::endl;
        std::cout << "viewPos: " << m_material.getShaderProgram().getUniformVec3("viewPos").x << " " << m_material.getShaderProgram().getUniformVec3("viewPos").y << " " << m_material.getShaderProgram().getUniformVec3("viewPos").z << std::endl;
        std::cout << "model: " << m_material.getShaderProgram().getUniformMat4("model")[0][0] << " " << m_material.getShaderProgram().getUniformMat4("model")[0][1] << " " << m_material.getShaderProgram().getUniformMat4("model")[0][2] << " " << m_material.getShaderProgram().getUniformMat4("model")[0][3] << std::endl;
        std::cout << "projection: " << m_material.getShaderProgram().getUniformMat4("projection")[0][0] << " " << m_material.getShaderProgram().getUniformMat4("projection")[0][1] << " " << m_material.getShaderProgram().getUniformMat4("projection")[0][2] << " " << m_material.getShaderProgram().getUniformMat4("projection")[0][3] << std::endl;
        std::cout << "view: " << m_material.getShaderProgram().getUniformMat4("view")[0][0] << " " << m_material.getShaderProgram().getUniformMat4("view")[0][1] << " " << m_material.getShaderProgram().getUniformMat4("view")[0][2] << " " << m_material.getShaderProgram().getUniformMat4("view")[0][3] << std::endl;
        std::cout << "Binding VAO: " << m_VAO << std::endl;
        std::cout << "DEBUG END\n" << std::endl;
        
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_meshFilter.getIndices().size(), GL_UNSIGNED_INT, nullptr);
        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << err << std::endl;
        }
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