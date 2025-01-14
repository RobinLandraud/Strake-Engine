#pragma once

#include <GL/glew.h>
#include <Strake/Dispatcher/EventDispatcher.hpp>
#include <Strake/Dispatcher/EventData.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_Transform.hpp>
#include <Strake/Material/Material.hpp>
#include <Strake/Component/Component.hpp>
#include <Strake/Component/MeshFilter.hpp>
#include <Strake/Component/Camera.hpp>
#include <Strake/Component/Transform.hpp>
#include <Strake/Component/Light/Light.hpp>
#include <Strake/Component/Light/DirectionalLight.hpp>
#include <Strake/Component/Light/PointLight.hpp>

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