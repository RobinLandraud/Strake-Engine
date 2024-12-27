#pragma once

#include <ECS/Component.hpp>
#include <ECS/Transform.hpp>
#include <ECS/EventDispatcher.hpp>
#include <ECS/Shaders.hpp>

namespace ECS {
    enum class LightType {
        Directional,
        Point,
        Spot
    };

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

    class Light: public Component
    {
        public:
            void setColor(const glm::vec3 &color);
            void setIntensity(float intensity);
            void setMinIntensity(float minIntensity);

            [[nodiscard]] float getIntensity() const;
            [[nodiscard]] float getMinIntensity() const;
            [[nodiscard]] const glm::vec3 &getColor() const;
            [[nodiscard]] LightType getType() const;

            void update() override;
            ShadowMap &getShadowMap();

        protected:

            explicit Light(GameObject &parent, LightType type);
            ~Light() override;

            LightType m_type;

            glm::vec3 m_color;
            float m_intensity;
            float m_minIntensity;

            ShadowMap m_shadowMap;
    };

    class PointLight : public Light
    {
        public:
            PointLight(GameObject &parent);

            void setPosition(const glm::vec3 &position);

            [[nodiscard]] const glm::vec3 getPosition() const;

        private:
            Transform &r_transform; // for position
    };

    class DirectionalLight : public Light
    {
        public:
            DirectionalLight(GameObject &parent);

            void setRotation(const glm::vec3 &rotation);
            void setDirection(const glm::vec3 &direction);

            [[nodiscard]] glm::vec3 getDirection() const;

        private:
            Transform &r_transform; // for rotation
    };
}