#include <ECS/MeshFilter.hpp>

namespace ECS {
    Cube::Cube(GameObject &parent)
        : MeshFilter(parent)
    {
        m_vertices = {
            // Front face
            glm::vec3(-0.5f, -0.5f,  0.5f), // bottom left
            glm::vec3( 0.5f, -0.5f,  0.5f), // bottom right
            glm::vec3( 0.5f,  0.5f,  0.5f), // top right
            glm::vec3(-0.5f,  0.5f,  0.5f), // top left

            // Back face
            glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left
            glm::vec3( 0.5f, -0.5f, -0.5f), // bottom right
            glm::vec3( 0.5f,  0.5f, -0.5f), // top right
            glm::vec3(-0.5f,  0.5f, -0.5f), // top left

            // Left face
            glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left
            glm::vec3(-0.5f, -0.5f,  0.5f), // bottom right
            glm::vec3(-0.5f,  0.5f,  0.5f), // top right
            glm::vec3(-0.5f,  0.5f, -0.5f), // top left

            // Right face
            glm::vec3( 0.5f, -0.5f, -0.5f), // bottom left
            glm::vec3( 0.5f, -0.5f,  0.5f), // bottom right
            glm::vec3( 0.5f,  0.5f,  0.5f), // top right
            glm::vec3( 0.5f,  0.5f, -0.5f), // top left

            // Top face
            glm::vec3(-0.5f,  0.5f, -0.5f), // bottom left
            glm::vec3( 0.5f,  0.5f, -0.5f), // bottom right
            glm::vec3( 0.5f,  0.5f,  0.5f), // top right
            glm::vec3(-0.5f,  0.5f,  0.5f), // top left

            // Bottom face
            glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left
            glm::vec3( 0.5f, -0.5f, -0.5f), // bottom right
            glm::vec3( 0.5f, -0.5f,  0.5f), // top right
            glm::vec3(-0.5f, -0.5f,  0.5f)  // top left
        };

        m_normals = {
            // Front face
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),

            // Back face
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),

            // Left face
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),

            // Right face
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),

            // Top face
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),

            // Bottom face
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f)
        };

        m_uvs = {
            // Front face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Back face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Left face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Right face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Top face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),

            // Bottom face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f)
        };

        m_indices = {
            // Front face (CCW)
            0, 1, 2,
            2, 3, 0,

            // Back face (CW)
            4, 6, 5,
            6, 4, 7,

            // Left face (CCW)
            8, 9, 10,
            10, 11, 8,

            // Right face (CCW)
            13, 12, 14,
            15, 14, 12,

            // Top face (CCW)
            17, 16, 18,
            19, 18, 16,

            // Bottom face (CCW)
            20, 21, 22,
            22, 23, 20
        };
    }
}