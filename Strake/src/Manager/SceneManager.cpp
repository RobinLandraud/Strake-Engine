#include <Strake/Manager/SceneManager.hpp>

namespace Strake {
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
}