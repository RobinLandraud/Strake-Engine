#include <ECS/Application.hpp>

namespace ECS {
    Material &MaterialManager::addMaterial(const std::string &name) {
        m_materials[name] = std::make_unique<Material>();
        return *m_materials[name];
    }

    Material &MaterialManager::getMaterial(const std::string &name) {
        return *m_materials.at(name);
    }

    void MaterialManager::removeMaterial(const std::string &name) {
        m_materials.erase(name);
    }

    void MaterialManager::clear() {
        m_materials.clear();
    }

    Texture &TextureManager::getTexture(const std::string &name) {
        return *m_textures.at(name);
    }

    void TextureManager::removeTexture(const std::string &name) {
        m_textures.erase(name);
    }

    void TextureManager::clear() {
        m_textures.clear();
    }

    Scene &SceneManager::addScene(const std::string &name) {
        m_scenes.emplace(name, std::make_unique<Scene>());
        if (!m_currentScene.has_value()) {
            m_currentScene = std::make_pair(name, std::ref(*m_scenes.at(name)));
        }
        return *m_scenes.at(name);
    }

    void SceneManager::setCurrentScene(const std::string &name) {
        m_currentScene = std::make_pair(name, std::ref(*m_scenes.at(name)));
    }

    Scene &SceneManager::getScene(const std::string &name) {
        return *m_scenes.at(name);
    }

    std::optional<std::pair<std::string, std::reference_wrapper<Scene>>> &SceneManager::getCurrentScene() {
        return m_currentScene;
    }

    std::unordered_map<std::string, std::unique_ptr<Scene>> &SceneManager::getScenes() {
        return m_scenes;
    }

    void SceneManager::removeScene(const std::string &name) {
        m_scenes.erase(name);
    }

    void SceneManager::clear() {
        m_scenes.clear();
    }

    Application::Application(std::string &&title, int width, int height, int fps) :
        m_gameLoop(fps),
        m_window(width, height, std::move(title))
    {
        ECS::init();
        ECS::EventHandler::init(m_window);
        ECS::Time::init();
    }

    Application::~Application() {
        m_materialManager.clear();
        m_textureManager.clear();
        ECS::EventHandler::destroy();
        ECS::Time::destroy();
        ECS::exit();
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

    Window &Application::getWindow() {
        return m_window;
    }

    void Application::run() {
        for (auto &scene : m_sceneManager.getScenes()) {
            scene.second->awake();
        }
        auto &scene = m_sceneManager.getCurrentScene();
        if (!scene.has_value()) {
            throw std::runtime_error("No scene set");
        }
        m_gameLoop.run(m_window, scene->second.get(), false);
    }
}