#include <ECS/Application/GameLoop.hpp>
#include <ECS/Manager/MaterialManager.hpp>
#include <ECS/Manager/textureManager.hpp>
#include <ECS/Manager/SceneManager.hpp>
#include <ECS/Window/Window.hpp>
#include <ECS/init.hpp>

namespace Strake {
    class Application {
        public:
            Application(std::string &&title, int width, int height, int fps);
            ~Application();
            void run();
            void run(bool debug);
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