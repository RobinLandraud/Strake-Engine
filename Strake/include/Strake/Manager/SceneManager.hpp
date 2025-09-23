#pragma once

#include <Strake/Scene/Scene.hpp>

namespace Strake {
    class SceneManager {
        public:
            SceneManager(const LayerManager &layerManager);
            ~SceneManager() = default;
            Scene &addScene(const std::string &name);
            void setCurrentScene(const std::string &name);
            Scene &getScene(const std::string &name);
            std::optional<std::pair<std::string, std::reference_wrapper<Scene>>> &getCurrentScene();
            std::unordered_map<std::string, std::unique_ptr<Scene>> &getScenes();
            void removeScene(const std::string &name);
            void clear();
        private:
            const LayerManager &r_layerManager;
            std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
            std::optional<std::pair<std::string, std::reference_wrapper<Scene>>> m_currentScene;
    };
}