#include <Strake/Application/Application.hpp>

namespace Strake {
    Application::Application(std::string &&title, int width, int height, int fps) :
        m_gameLoop(fps),
        m_window(width, height, std::move(title)),
        m_layerManager(),
        m_materialManager(),
        m_textureManager(),
        m_sceneManager(m_layerManager)
    {
        Strake::init();
        Strake::EventHandler::init(m_window);
        Strake::Time::init();
    }

    Application::~Application() {
        m_materialManager.clear();
        m_textureManager.clear();
        Strake::EventHandler::destroy();
        Strake::Time::destroy();
        Strake::exit();
    }

    MaterialManager &Application::getMaterialManager() {
        return m_materialManager;
    }

    TextureManager &Application::getTextureManager() {
        return m_textureManager;
    }

    SceneManager &Application::getSceneManager() {
        return m_sceneManager;
    }

    LayerManager &Application::getLayerManager() {
        return m_layerManager;
    }

    Window &Application::getWindow() {
        return m_window;
    }

    void Application::run() {
        run(false);
    }

    void Application::run(bool debug) {
        for (auto &scene : m_sceneManager.getScenes()) {
            scene.second->awake();
        }
        auto &scene = m_sceneManager.getCurrentScene();
        if (!scene.has_value()) {
            throw std::runtime_error("No scene set");
        }
        m_gameLoop.run(m_window, scene->second.get(), debug);
    }
}