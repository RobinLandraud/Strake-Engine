#include <Strake/Application/GameLoop.hpp>
#include <Strake/Manager/MaterialManager.hpp>
#include <Strake/Manager/textureManager.hpp>
#include <Strake/Manager/SceneManager.hpp>
#include <Strake/Manager/LayerManager.hpp>
#include <Strake/Manager/PhysicsManager/PhysicsManager.hpp>
#include <Strake/Window/Window.hpp>
#include <Strake/init.hpp>

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
            LayerManager &getLayerManager();
            Window &getWindow();

        private:
            Window m_window;
            GameLoop m_gameLoop;

            LayerManager m_layerManager;
            MaterialManager m_materialManager;
            TextureManager m_textureManager;
            SceneManager m_sceneManager;
    };
}