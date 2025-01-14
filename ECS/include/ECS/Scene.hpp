#pragma once

#include <ECS/Component.hpp>
#include <ECS/GameObject.hpp>
#include <ECS/Component/Camera.hpp>
#include <ECS/Manager/LightManager.hpp>
#include <ECS/Manager/RendererManager.hpp>
#include <functional>
#include <optional>
#include <ECS/Component/MeshFilter.hpp>
#include <ECS/Shader/ShaderProgram.hpp>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace Strake {
    class Scene {
        public:
            Scene();
            ~Scene() = default;
            Scene(const Scene &other) = delete;
            Scene(Scene &&other) = delete;
            Scene &operator=(const Scene &other) = delete;
            Scene &operator=(Scene &&other) = delete;

            GameObject &addGameObject(const std::string &name);
            GameObject &loadFromFile(const std::string &path);
            void removeGameObject(const std::string &name);
            void removeGameObject(GameObject &gameObject);
            GameObject &getGameObject(const std::string &name);
            [[nodiscard]] const std::unordered_map<std::string, std::unique_ptr<GameObject>> &getGameObjects() const;

            void setMainCamera(Camera &camera);
            [[nodiscard]] Camera &getMainCamera() const;

            void awake();
            void start();
            void update();
            void fixedUpdate();
            void lateUpdate();
            void render(int width, int height);

        private:
            // order is important
            EventDispatcher m_eventDispatcher;

            //render pipeline
            ShaderProgram m_shadowShaderProgram;
            LightManager m_lightManager;
            RendererManager m_rendererManager;

            std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
            std::optional<std::reference_wrapper<Camera>> m_mainCamera;
    };
}