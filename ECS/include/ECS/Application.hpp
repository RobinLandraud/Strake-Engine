#include <ECS/GameLoop.hpp>
#include <ECS/Material.hpp>
#include <ECS/Window.hpp>
#include <ECS/init.hpp>
#include <ECS/EventDispatcher.hpp>

namespace ECS {
    class MaterialManager {
        public:
            MaterialManager() = default;
            ~MaterialManager() = default;
            Material &addMaterial(const std::string &name);
            Material &getMaterial(const std::string &name);
            void removeMaterial(const std::string &name);
            void clear();
        private:
            std::unordered_map<std::string, std::unique_ptr<Material>> m_materials;
    };

    class TextureManager {
        public:
            TextureManager() = default;
            ~TextureManager() = default;

            template <typename T, typename... Args>
            inline Texture &addTexture(const std::string &name, Args&&... args) {
                static_assert(std::is_base_of<Texture, T>::value, "T must be derived from Texture");

                m_textures[name] = std::make_unique<T>(std::forward<Args>(args)...);
                if (!m_textures[name]->isLoaded()) {
                    throw std::runtime_error("Failed to load texture");
                }
                return *m_textures[name];
            }

            Texture &getTexture(const std::string &name);
            void removeTexture(const std::string &name);
            void clear();
        private:
            std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
    };

    class SceneManager {
        public:
            SceneManager() = default;
            ~SceneManager() = default;
            Scene &addScene(const std::string &name);
            void setCurrentScene(const std::string &name);
            Scene &getScene(const std::string &name);
            std::optional<std::pair<std::string, std::reference_wrapper<Scene>>> &getCurrentScene();
            std::unordered_map<std::string, std::unique_ptr<Scene>> &getScenes();
            void removeScene(const std::string &name);
            void clear();
        private:
            std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
            std::optional<std::pair<std::string, std::reference_wrapper<Scene>>> m_currentScene;
    };

    class Application {
        public:
            Application(std::string &&title, int width, int height, int fps);
            ~Application();
            void run();
            MaterialManager &getMaterialManager();
            TextureManager &getTextureManager();
            SceneManager &getSceneManager();
            Window &getWindow();

        private:
            Window m_window;
            GameLoop m_gameLoop;

            MaterialManager m_materialManager;
            TextureManager m_textureManager;
            SceneManager m_sceneManager;
    };
}