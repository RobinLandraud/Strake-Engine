#include <ECS/Scene.hpp>

namespace ECS {
    Scene::Scene()
    {
    }

    GameObject &Scene::addGameObject(const std::string &name)
    {
        m_gameObjects[name] = std::make_unique<GameObject>(name);
        return *m_gameObjects[name];
    }

    void Scene::removeGameObject(const std::string &name)
    {
        m_gameObjects.erase(name);
    }

    void Scene::removeGameObject(GameObject &gameObject)
    {
        m_gameObjects.erase(gameObject.getName());
    }

    GameObject &Scene::getGameObject(const std::string &name)
    {
        return *m_gameObjects[name];
    }

    const std::unordered_map<std::string, std::unique_ptr<GameObject>> &Scene::getGameObjects() const
    {
        return m_gameObjects;
    }

    void Scene::setMainCamera(Camera &camera)
    {
        m_mainCamera = camera;
    }

    Camera &Scene::getMainCamera() const
    {
        if (!m_mainCamera.has_value()) {
            throw std::runtime_error("Main camera is not set");
        }
        return m_mainCamera.value();
    }

    void Scene::awake()
    {
        for (auto &gameObject : m_gameObjects) {
            gameObject.second->awake();
        }
    }

    void Scene::start()
    {
        for (auto &gameObject : m_gameObjects) {
            gameObject.second->start();
        }
    }

    void Scene::update()
    {
        for (auto &gameObject : m_gameObjects) {
            gameObject.second->update();
        }
    }

    void Scene::fixedUpdate()
    {
        for (auto &gameObject : m_gameObjects) {
            gameObject.second->fixedUpdate();
        }
    }

    void Scene::lateUpdate()
    {
        for (auto &gameObject : m_gameObjects) {
            gameObject.second->lateUpdate();
        }
    }

    void Scene::render()
    {
        for (auto &gameObject : m_gameObjects) {
            gameObject.second->render();
        }
    }
}