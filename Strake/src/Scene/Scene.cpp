#include <Strake/Scene/Scene.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Strake {
    Scene::Scene(const LayerManager &layerManager) :
        m_eventDispatcher(),
        r_layerManager(layerManager),
        m_lightManager(m_eventDispatcher),
        m_rendererManager(m_eventDispatcher),
        m_scriptManager(m_eventDispatcher),
        m_physicsManager(m_eventDispatcher)
    {
    }

    GameObject &Scene::addGameObject(const std::string &name)
    {
        m_gameObjects[name] = std::make_unique<GameObject>(name, *this, m_eventDispatcher, r_layerManager.getLayer(0));
        return *m_gameObjects[name];
    }

    GameObject &Scene::addGameObject(const std::string &name, Layer &layer)
    {
        m_gameObjects[name] = std::make_unique<GameObject>(name, *this, m_eventDispatcher, layer);
        return *m_gameObjects[name];
    }

    GameObject &Scene::addGameObject(const std::string &name, int layer)
    {
        m_gameObjects[name] = std::make_unique<GameObject>(name, *this,  m_eventDispatcher, r_layerManager.getLayer(layer));
        return *m_gameObjects[name];
    }

    GameObject &Scene::addGameObject(const std::string &name, const std::string &layer)
    {
        m_gameObjects[name] = std::make_unique<GameObject>(name, *this, m_eventDispatcher, r_layerManager.getLayer(layer));
        return *m_gameObjects[name];
    }

    std::pair<GameObject &, std::vector<std::reference_wrapper<GameObject>>> Scene::loadFromFile(const std::string &path) {
        std::string name = path.substr(path.find_last_of('/') + 1);
        name = name.substr(0, name.find_last_of('.'));
        GameObject &mainObj = addGameObject(name);
        mainObj.addComponent<MeshFilter>();
        std::cout << "Loading " << name << std::endl;
        return std::make_pair(std::ref(mainObj), mainObj.getComponent<MeshFilter>().loadFromFile(path));
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

    const LayerManager &Scene::getLayerManager() const
    {
        return r_layerManager;
    }

    void Scene::awake()
    {
        m_scriptManager.awake();
    }

    void Scene::start()
    {
        m_scriptManager.start();
    }

    void Scene::update()
    {
        m_scriptManager.update();
    }

    void Scene::fixedUpdate()
    {
        m_physicsManager.physicsUpdate();
        m_scriptManager.fixedUpdate();
    }

    void Scene::lateUpdate()
    {
        m_scriptManager.lateUpdate();
    }

    void Scene::render(int winWidth, int winHeight) // render pipeline
    {
        Camera &mainCamera = getMainCamera();
        mainCamera.updateFrustrum();
        for (const auto & [layer, _] : m_rendererManager.getRenderers()) {
            m_rendererManager.clearDepth();
            m_lightManager.clearObjects(layer);
            std::vector<std::reference_wrapper<Renderer>> in_frustrum_renderers = m_rendererManager.updateLightings(
                layer,
                m_lightManager.getLights(layer)
            );
            m_lightManager.renderShadowMaps(layer, winWidth, winHeight);
            for (auto &renderer : in_frustrum_renderers) {
                renderer.get().render(mainCamera);
            }
        }
    }
}