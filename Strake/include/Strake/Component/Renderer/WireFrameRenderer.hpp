#pragma once

#include <Strake/Component/Renderer/Renderer.hpp>
#include <Strake/Shader/ShaderProgram.hpp>
#include <Strake/Component/Collider/Collider.hpp>
#include <Strake/Component/Camera.hpp>
#include <Strake/Component/Transform.hpp>
#include <vector>
#include <glm/glm.hpp>

namespace Strake {
    class WireFrameRenderer : public Renderer
    {
        public:
            WireFrameRenderer(GameObject &parent, MeshFilter &mesh, glm::vec3 offset = glm::vec3(0.0f));
            WireFrameRenderer(GameObject &parent, Collider &collider);
            ~WireFrameRenderer();

            virtual void render(Camera &camera) final;
            void GLrender();

            void setLineWidth(float lineWidth);
            void setLineColor(const glm::vec3 &lineColor);
            [[nodiscard]] float getLineWidth() const;
            [[nodiscard]] const glm::vec3 &getLineColor() const;

        private:
            GLuint m_VAO;
            GLuint m_VBO;
            GLuint m_EBO;
            MeshFilter &r_mesh;
            glm::vec3 m_offset;
            float m_lineWidth;
            glm::vec3 m_lineColor;
            ShaderProgram m_shaderProgram;

            void setupMesh();
    };
}
