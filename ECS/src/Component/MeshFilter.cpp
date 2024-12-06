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

    void MeshFilter::loadFromOBJ(const std::string &path) {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        std::vector<unsigned int> indices;

        std::map<PackedVertex, unsigned int> vertexToIndexMap;
        std::vector<glm::vec3> orderedVertices;
        std::vector<glm::vec2> orderedUVs;
        std::vector<glm::vec3> orderedNormals;
        std::vector<unsigned int> newIndices;

        FILE *file = fopen(path.c_str(), "r");
        if (file == nullptr) {
            std::cerr << "Failed to open file: " << path << std::endl;
            return;
        }

        while (true) {
            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF) {
                break;
            }

            if (strcmp(lineHeader, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                vertices.push_back(vertex);
            } else if (strcmp(lineHeader, "vt") == 0) {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                uv.y = 1.0f - uv.y; // Flip V-coordinate for OpenGL
                uvs.push_back(uv);
            } else if (strcmp(lineHeader, "vn") == 0) {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                normals.push_back(normal);
            }else if (strcmp(lineHeader, "f") == 0) {
                unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
                                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                    &vertexIndex[2], &uvIndex[2], &normalIndex[2],
                                    &vertexIndex[3], &uvIndex[3], &normalIndex[3]);

                if (matches == 9) { // Triangle face
                    for (int i = 0; i < 3; i++) {
                        PackedVertex packed = {
                            vertices[vertexIndex[i] - 1],
                            uvs[uvIndex[i] - 1],
                            normals[normalIndex[i] - 1]
                        };

                        auto it = vertexToIndexMap.find(packed);
                        if (it != vertexToIndexMap.end()) {
                            newIndices.push_back(it->second);
                        } else {
                            orderedVertices.push_back(packed.position);
                            orderedUVs.push_back(packed.uv);
                            orderedNormals.push_back(packed.normal);
                            unsigned int newIndex = (unsigned int)orderedVertices.size() - 1;
                            newIndices.push_back(newIndex);
                            vertexToIndexMap[packed] = newIndex;
                        }
                    }
                } else if (matches == 12) { // Quad face
                    // First triangle: v1, v2, v3
                    for (int i = 0; i < 3; i++) {
                        PackedVertex packed = {
                            vertices[vertexIndex[i] - 1],
                            uvs[uvIndex[i] - 1],
                            normals[normalIndex[i] - 1]
                        };

                        auto it = vertexToIndexMap.find(packed);
                        if (it != vertexToIndexMap.end()) {
                            newIndices.push_back(it->second);
                        } else {
                            orderedVertices.push_back(packed.position);
                            orderedUVs.push_back(packed.uv);
                            orderedNormals.push_back(packed.normal);
                            unsigned int newIndex = (unsigned int)orderedVertices.size() - 1;
                            newIndices.push_back(newIndex);
                            vertexToIndexMap[packed] = newIndex;
                        }
                    }

                    // Second triangle: v1, v3, v4
                    for (int i : {0, 2, 3}) {
                        PackedVertex packed = {
                            vertices[vertexIndex[i] - 1],
                            uvs[uvIndex[i] - 1],
                            normals[normalIndex[i] - 1]
                        };

                        auto it = vertexToIndexMap.find(packed);
                        if (it != vertexToIndexMap.end()) {
                            newIndices.push_back(it->second);
                        } else {
                            orderedVertices.push_back(packed.position);
                            orderedUVs.push_back(packed.uv);
                            orderedNormals.push_back(packed.normal);
                            unsigned int newIndex = (unsigned int)orderedVertices.size() - 1;
                            newIndices.push_back(newIndex);
                            vertexToIndexMap[packed] = newIndex;
                        }
                    }
                } else {
                    std::cerr << "Unsupported face format in OBJ file" << std::endl;
                    fclose(file);
                    return;
                }
            }
        }

        fclose(file);
        // Pass the ordered data to your mesh
        setVertices(orderedVertices);
        setNormals(orderedNormals);
        setUVs(orderedUVs);
        setIndices(newIndices);

        m_isUpdated = true;
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