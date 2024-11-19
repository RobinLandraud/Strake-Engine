#pragma once

#include <ECS/Component.hpp>
#include <ECS/GameObject.hpp>
#include <ECS/Camera.hpp>
#include <functional>
#include <optional>

namespace ECS {
    class Scene {
        public:
            Scene();
            ~Scene() = default;
            Scene(const Scene &other) = delete;
            Scene(Scene &&other) = delete;
            Scene &operator=(const Scene &other) = delete;
            Scene &operator=(Scene &&other) = delete;

            GameObject &addGameObject(const std::string &name);
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
            void render();

        private:
            std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
            std::optional<std::reference_wrapper<Camera>> m_mainCamera;
    };
}