#pragma once

#include <Strake/Component/Component.hpp>
#include <Strake/GameObject/GameObject.hpp>
#include <Strake/Component/Camera.hpp>

#include <Strake/Manager/LightManager.hpp>
#include <Strake/Manager/LayerManager.hpp>
#include <Strake/Manager/RendererManager.hpp>
#include <Strake/Manager/ScriptManager.hpp>
#include <Strake/Manager/PhysicsManager/PhysicsManager.hpp>

#include <functional>
#include <optional>
#include <Strake/Component/MeshFilter/MeshFilter.hpp>
#include <Strake/Component/Renderer/MeshRenderer.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Strake {
    class Scene {
        public:
            Scene(const LayerManager &layerManager);
            ~Scene() = default;
            Scene(const Scene &other) = delete;
            Scene(Scene &&other) = delete;
            Scene &operator=(const Scene &other) = delete;
            Scene &operator=(Scene &&other) = delete;

            GameObject &addGameObject(const std::string &name);
            GameObject &addGameObject(const std::string &name, Layer &layer);
            GameObject &addGameObject(const std::string &name, int layer);
            GameObject &addGameObject(const std::string &name, const std::string &layer);
            std::pair<GameObject &, std::vector<std::reference_wrapper<GameObject>>> loadFromFile(const std::string &path);
            void removeGameObject(const std::string &name);
            void removeGameObject(GameObject &gameObject);
            GameObject &getGameObject(const std::string &name);
            [[nodiscard]] const std::unordered_map<std::string, std::unique_ptr<GameObject>> &getGameObjects() const;

            void setMainCamera(Camera &camera);
            [[nodiscard]] Camera &getMainCamera() const;

            [[nodiscard]] const LayerManager &getLayerManager() const;

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
            const LayerManager &r_layerManager;
            LightManager m_lightManager;
            RendererManager m_rendererManager;
            ScriptManager m_scriptManager;
            PhysicsManager m_physicsManager; // handle all physics managers (collision, rigidbody, etc) for objects in the scene

            std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
            std::optional<std::reference_wrapper<Camera>> m_mainCamera;
    };
}