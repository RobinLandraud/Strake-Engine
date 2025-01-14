#pragma once

#include <GL/glew.h>
#include <ECS/Dispatcher/EventDispatcher.hpp>
#include <ECS/Dispatcher/EventData.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_Transform.hpp>
#include <ECS/Material/Material.hpp>
#include <ECS/Component/Component.hpp>
#include <ECS/Component/MeshFilter.hpp>
#include <ECS/Component/Camera.hpp>
#include <ECS/Component/Transform.hpp>
#include <ECS/Component/Light/Light.hpp>
#include <ECS/Component/Light/DirectionalLight.hpp>
#include <ECS/Component/Light/PointLight.hpp>

namespace Strake {
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
            void GLrender();

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