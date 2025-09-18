#pragma once

#include <GL/glew.h>
#include <Strake/Dispatcher/EventDispatcher.hpp>
#include <Strake/Dispatcher/EventData.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Strake/Material/Material.hpp>
#include <Strake/Component/Renderer/Renderer.hpp>
#include <Strake/Component/MeshFilter/MeshFilter.hpp>
#include <Strake/Component/Camera.hpp>
#include <Strake/Component/Transform.hpp>
#include <Strake/Component/Light/Light.hpp>
#include <Strake/Component/Light/DirectionalLight.hpp>
#include <Strake/Component/Light/PointLight.hpp>

namespace Strake {
    class MeshRenderer : public Renderer
    {
        public:
            MeshRenderer(GameObject &parent, MeshFilter &meshFilter, Material &material);
            MeshRenderer(GameObject &parent, Material &material);

            MeshRenderer(const MeshRenderer &other) = delete;
            MeshRenderer(MeshRenderer &&other) = delete;
            MeshRenderer &operator=(const MeshRenderer &other) = delete;
            MeshRenderer &operator=(MeshRenderer &&other) = delete;
            ~MeshRenderer() override;

            virtual void preRender() final;
            virtual void render(Camera &camera) final;
            void GLrender();

            [[nodiscard]] const MeshFilter &getMeshFilter() const;
            [[nodiscard]] const Material &getMaterial() const;

            void updateLights(std::vector<std::reference_wrapper<Light>> &lights);
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