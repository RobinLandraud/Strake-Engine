#include <ECS/Scene.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace ECS {
    Scene::Scene() :
        m_eventDispatcher(),
        m_lightManager(m_eventDispatcher)
    {
    }

    GameObject &Scene::addGameObject(const std::string &name)
    {
        m_gameObjects[name] = std::make_unique<GameObject>(name, m_eventDispatcher);
        return *m_gameObjects[name];
    }

    GameObject &Scene::loadFromFile(const std::string &path) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw std::runtime_error("Failed to load mesh file: " + path);
        }

        if (scene->mNumMeshes == 0) {
            throw std::runtime_error("No meshes found in file: " + path);
        }
        std::cout << "path: " << path << std::endl;
        std::cout << "num meshes: " << scene->mNumMeshes << std::endl;

        std::string pathName = path.substr(path.find_last_of('/') + 1);
        pathName = pathName.substr(0, pathName.find_last_of('.'));

        ECS::GameObject &mainObj = addGameObject(pathName);

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            std::string name = static_cast<std::string>(scene->mMeshes[i]->mName.C_Str());
            ECS::GameObject &obj = mainObj.addChild(name);
            obj.addComponent<ECS::MeshFilter>();
            obj.getComponent<ECS::MeshFilter>().loadFromFile(path, i);
        }

        return mainObj;
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
        if (!m_mainCamera.has_value()) {
            return;
        }
        for (auto &gameObject : m_gameObjects) {
            gameObject.second->render(m_mainCamera.value().get());
        }
    }
}