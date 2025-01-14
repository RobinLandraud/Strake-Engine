#include <Strake/Config/Config.hpp>
#include <Strake/Application/GameLoop.hpp>
#include <Strake/Script/Script.hpp>
#include <Strake/Material/Material.hpp>
#include <Strake/Component/Component.hpp>
#include <Strake/Component/Camera.hpp>
#include <Strake/Component/Transform.hpp>
#include <Strake/Component/MeshFilter.hpp>
#include <Strake/Component/MeshRenderer.hpp>
#include <Strake/Scene/Scene.hpp>
#include <Strake/Window/EventHandler.hpp>
#include <Strake/Application/Application.hpp>
#include <Strake/init.hpp>

class Rotator : public Strake::Script
{
    public:
        Rotator(Strake::GameObject &parent, float speed) :
            Strake::Script(parent),
            m_speed(speed)
        {

        }
        void awake() override {
            r_transform = getParent().getTransform();
        }
        void fixedUpdate() override {
            r_transform->get().rotateLocal(glm::vec3(0.0f, 0.0f, m_speed));
        }
    private:
        std::optional<std::reference_wrapper<Strake::Transform>> r_transform;
        float m_speed;
};

class Scaler : public Strake::Script
{
    public:
        using Strake::Script::Script;
        void awake() override {
            r_transform = getParent().getTransform();
        }
        void fixedUpdate() override {
            Strake::Transform &transform = r_transform.value();
            if (transform.getLocalScale().x > 2.0f) {
                m_scaleFactor = 0.999f;
            }
            if (transform.getLocalScale().x < 0.5f) {
                m_scaleFactor = 1.001f;
            }
            transform.scaleLocal(glm::vec3(m_scaleFactor, 1.000f, m_scaleFactor));
        }
    private:
        float m_scaleFactor = 1.001f;
        std::optional<std::reference_wrapper<Strake::Transform>> r_transform;
};

class CharacterController: public Strake::Script
{
    public:
        using Strake::Script::Script;
        void awake() override {
            transform = getParent().getTransform();
        }
        void update() override {
            const Strake::mouse_t &mouse = Strake::EventHandler::getMouse();
            Strake::Transform &transform = this->transform.value();
            //std::cout << "Mouse: " << mouse.x << " " << mouse.y << std::endl;
            if (Strake::EventHandler::isKeyHeld(Strake::Key::W)) {
                transform.translateLocal(glm::vec3(0.0f, 0.0f, m_speed * Strake::Time::getDeltaTime()));
                //std::cout << "Z key pressed" << std::endl;
            } else if (Strake::EventHandler::isKeyHeld(Strake::Key::S)) {
                transform.translateLocal(glm::vec3(0.0f, 0.0f, -m_speed * Strake::Time::getDeltaTime()));
            }
            if (Strake::EventHandler::isKeyHeld(Strake::Key::A)) {
                transform.translateLocal(glm::vec3(-m_speed * Strake::Time::getDeltaTime(), 0.0f, 0.0f));
            } else if (Strake::EventHandler::isKeyHeld(Strake::Key::D)) {
                transform.translateLocal(glm::vec3(m_speed * Strake::Time::getDeltaTime(), 0.0f, 0.0f));
            }
            if (Strake::EventHandler::isKeyHeld(Strake::Key::Space)) {
                transform.translateLocal(glm::vec3(0.0f, m_speed * Strake::Time::getDeltaTime(), 0.0f));
            } else if (Strake::EventHandler::isKeyHeld(Strake::Key::LeftShift)) {
                transform.translateLocal(glm::vec3(0.0f, -m_speed * Strake::Time::getDeltaTime(), 0.0f));
            }
            //look at mouse
            float yaw = mouse.x;
            float roll = mouse.y;
            transform.setLocalRotation(glm::vec3(-roll, -yaw, 0.0f));
        }
    private:
        std::optional<std::reference_wrapper<Strake::Transform>> transform;
        const float m_speed = 10.0f;
};

void printComponent(Strake::GameObject &go, int depth)
{
    for (int i = 0; i < depth; i++) {
        std::cout << "\t";
    }
    std::cout << "* " << go.getName() << " {" << "\n";
    auto &comp = go.getComponents();
    for (auto &c : comp) {
        for (int i = 0; i < depth; i++) {
            std::cout << "\t";
        }
        std::cout << "\t- " << c.first.name() << "\n";
    }
    auto &children = go.getChildren();
    for (auto &child : children) {
        printComponent(*child.second, depth + 1);
    }
    for (int i = 0; i < depth; i++) {
        std::cout << "\t";
    }
    std::cout << "}" << std::endl;
}

Strake::Scene createScene(int width, int height)
{
    return Strake::Scene();
}

int game()
{
    GLuint error = 0;

    const int WIN_WIDTH = 1400;
    const int WIN_HEIGHT = 900;
    const int FPS = 144;

    std::cout << Strake::Config::getVersion() << std::endl;
    std::cout << Strake::Config::getGLFWVersion() << std::endl;

    Strake::Application app(
        "Strake Engine V" + Strake::Config::getVersion(),
        WIN_WIDTH, WIN_HEIGHT,
        FPS
    );
    app.getWindow().setBgColor(glm::vec4(0.0f, 0.0f, 255.0f, 1.0f));

    Strake::Scene &scene = app.getSceneManager().addScene("Main Scene");

    Strake::Texture &barelTexture = app.getTextureManager().addTexture<Strake::Texture2D>("barel", "assets/map.png");
    Strake::Material &barelMaterial = app.getMaterialManager().addMaterial("barel");
    barelMaterial.addTexture(barelTexture, "textureSampler");

    Strake::Texture &metalTexture = app.getTextureManager().addTexture<Strake::Texture2D>("metal", "assets/metal.png");
    Strake::Material &metalMaterial = app.getMaterialManager().addMaterial("metal");
    metalMaterial.addTexture(metalTexture, "textureSampler");
    metalMaterial.setShininess(256.0f);

    Strake::Texture &grassTexture = app.getTextureManager().addTexture<Strake::Texture2D>("grass", "assets/grass.png");
    Strake::Material &grassMaterial = app.getMaterialManager().addMaterial("grass");
    grassMaterial.addTexture(grassTexture, "textureSampler");
    grassMaterial.setShininess(10.0f);

    Strake::Texture &treeTexture = app.getTextureManager().addTexture<Strake::Texture2D>("tree", "assets/tree/textures/tree.png");
    Strake::Material &treeMaterial = app.getMaterialManager().addMaterial("tree");
    treeMaterial.addTexture(treeTexture, "textureSampler");

    Strake::GameObject &floor = scene.addGameObject("Floor");
    floor.addComponent<Strake::Cube>();
    floor.getTransform().setLocalScale(glm::vec3(20.0f, 0.1f, 20.0f));
    floor.getTransform().setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    floor.addComponent<Strake::MeshRenderer>(grassMaterial);

    Strake::GameObject &player = scene.addGameObject("Main Camera");
    player.addComponent<Strake::Camera>();
    Strake::Camera &cam = player.getComponent<Strake::Camera>();
    cam.setProjection(45.0f, static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT), 0.1f, 100.0f);
    player.getTransform().setLocalPosition(glm::vec3(0.0f, 2.0f, 5.0f));
    player.addComponent<CharacterController>();
    scene.setMainCamera(cam);

    Strake::GameObject &barrel = scene.addGameObject("Barrel");
    barrel.getTransform().setLocalPosition(glm::vec3(3.0f, 0.0f, 4.0f));
    barrel.addComponent<Strake::MeshFilter>();
    std::vector<std::reference_wrapper<Strake::GameObject>> nodes = barrel.getComponent<Strake::MeshFilter>().loadFromFile("assets/barrel.obj"); // load all mesh as children nodes
    for (auto &node : nodes) {
        node.get().addComponent<Strake::MeshRenderer>(barelMaterial);
    }

    Strake::GameObject &barrel2 = scene.addGameObject("Barrel2");
    barrel2.getTransform().setLocalPosition(glm::vec3(-3.0f, 0.0f, -4.0f));
    barrel2.addComponent<Strake::MeshFilter>();
    barrel2.getComponent<Strake::MeshFilter>().loadFromFile("assets/barrel.obj", 0); // load the first mesh directly in the game object
    barrel2.addComponent<Strake::MeshRenderer>(barelMaterial);

    Strake::GameObject &metalBox = scene.addGameObject("Metal Box");
    metalBox.getTransform().setLocalPosition(glm::vec3(4.0f, 0.5f, -3.0f));
    metalBox.addComponent<Strake::Cube>();
    metalBox.addComponent<Strake::MeshRenderer>(metalMaterial);

    Strake::GameObject &Moon = scene.addGameObject("Moon");
    Moon.getTransform().setLocalRotation(glm::vec3(0.0f, 0.0f, 180.0f));
    Moon.addComponent<Rotator>(0.2f);

    Strake::GameObject &light = Moon.addChild("Light");
    light.addComponent<Strake::PointLight>();
    light.getTransform().setLocalPosition(glm::vec3(0.0f, 30.0f, 0.0f));
    light.getComponent<Strake::PointLight>().setIntensity(0.5f);
    light.getComponent<Strake::PointLight>().setColor(glm::vec3(0.1f, 0.1f, 1.0f));

    Strake::GameObject &sun = scene.addGameObject("Sun");
    sun.addComponent<Rotator>(0.2f);
    sun.addComponent<Strake::DirectionalLight>();
    sun.getComponent<Strake::DirectionalLight>().setIntensity(1.0f);
    sun.getComponent<Strake::DirectionalLight>().setColor(glm::vec3(1.0f, 1.0f, 0.1f));

    Strake::GameObject &tree = scene.addGameObject("Tree");
    tree.addComponent<Strake::MeshFilter>();
    std::cout << "Loading tree" << std::endl;
    tree.getComponent<Strake::MeshFilter>().loadFromFile("assets/tree/source/tree.obj", 0);
    std::cout << "Tree loaded" << std::endl;
    tree.addComponent<Strake::MeshRenderer>(treeMaterial);

    for (auto &go : scene.getGameObjects()) {
        printComponent(*go.second, 0);
    }
    app.run(true);
    return 0;
}

int main()
{
    int out = game();
    std::cout << "Game exited with code: " << out << std::endl;
    return out;
}