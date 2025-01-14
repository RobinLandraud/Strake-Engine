#pragma once

#include <ECS/GameObject/GameObject.hpp>
#include <glm/gtc/matrix_Transform.hpp>
#include <GL/glew.h>

namespace Strake {
    class ShadowMap
    {
        public:
            ShadowMap();
            ~ShadowMap();

            [[nodiscard]] GLuint getShadowMap() const;
            [[nodiscard]] GLuint getShadowFBO() const;
            [[nodiscard]] const glm::mat4 &getLightProjection() const;
            [[nodiscard]] glm::vec2 getSize() const;

            void addObject(GameObject &object);
            [[nodiscard]] const std::vector<std::reference_wrapper<GameObject>> &getObjects() const;
            void clearObjects();

            void bind();
            void unbind();
        private:
            GLuint m_shadowFBO;
            GLuint m_shadowMap;
            glm::ivec2 m_size;
            glm::mat4 m_lightProjection;
            std::vector<std::reference_wrapper<GameObject>> m_objects;
    };
}