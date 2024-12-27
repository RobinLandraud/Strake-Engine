#pragma once

#include <GL/glew.h>
#include <ECS/Component.hpp>
#include <ECS/MeshFilter.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ECS/Material.hpp>
#include <ECS/Camera.hpp>
#include <ECS/Transform.hpp>
#include <ECS/Lights.hpp>

namespace ECS {
    class MeshRenderer : public Component
    {
        public:
            MeshRenderer(GameObject &parent, MeshFilter &meshFilter, Material &material);
            MeshRenderer(GameObject &parent, Material &material);

            MeshRenderer(const MeshRenderer &other) = delete;
            MeshRenderer(MeshRenderer &&other) = delete;
            MeshRenderer &operator=(const MeshRenderer &other) = delete;
            MeshRenderer &operator=(MeshRenderer &&other) = delete;
            ~MeshRenderer() override;

            void render(Camera &camera) override;

            void lateUpdate() override;

            [[nodiscard]] const MeshFilter &getMeshFilter() const;
            [[nodiscard]] const Material &getMaterial() const;

            void addLight(const Light &light);
            void clearLights();
            std::vector<std::reference_wrapper<const Light>> &getLights();

        private:
            GLuint m_VAO;
            GLuint m_VBO;
            GLuint m_EBO;
            MeshFilter &m_meshFilter;
            Material &m_material;

            std::vector<std::reference_wrapper<const Light>> m_lights;

            void setupMesh();
    };
}