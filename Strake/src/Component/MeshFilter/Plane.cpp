#include <Strake/Component/MeshFilter/Plane.hpp>

namespace Strake
{
    Plane::Plane(GameObject &parent) : MeshFilter(parent)
    {
        std::vector<glm::vec3> vertices = {
            // Front face
            glm::vec3(-0.5f, 0.0f, -0.5f), // bottom left
            glm::vec3(0.5f, 0.0f, -0.5f), // bottom right
            glm::vec3(0.5f, 0.0f, 0.5f), // top right
            glm::vec3(-0.5f, 0.0f, 0.5f), // top left
            // Back face
            glm::vec3(-0.5f, 0.0f, -0.5f), // bottom left
            glm::vec3(-0.5f, 0.0f, 0.5f), // top left
            glm::vec3(0.5f, 0.0f, 0.5f), // top right
            glm::vec3(0.5f, 0.0f, -0.5f) // bottom right
        };

        std::vector<glm::vec3> normals = {
            // Front face
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            // Back face
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f)
        };

        std::vector<glm::vec2> uvs = {
            // Front face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            // Back face
            glm::vec2(0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f)
        };

        std::vector<unsigned int> indices = {
            // Front face
            0, 2, 1,
            0, 3, 2,
            // Back face
            4, 6, 5,
            4, 7, 6
        };

        setVertices(vertices);
        setNormals(normals);
        setUVs(uvs);
        setIndices(indices);
    }
}