#include <Strake/Config/Config.hpp>
#include <Strake/Application/Application.hpp>
#include <Strake/Window/EventHandler.hpp>
#include <Strake/Application/GameLoop.hpp>
#include <Strake/Scene/Scene.hpp>
#include <Strake/Material/Material.hpp>
#include <Strake/Texture/Texture.hpp>
#include <Strake/Component/Camera.hpp>
#include <Strake/Component/Transform.hpp>
#include <Strake/Component/MeshFilter/MeshFilter.hpp>
#include <Strake/Component/MeshFilter/Cube.hpp>
#include <Strake/Component/MeshFilter/Plane.hpp>
#include <Strake/Component/MeshFilter/Sphere.hpp>
#include <Strake/Component/MeshFilter/Capsule.hpp>
#include <Strake/Component/Renderer/MeshRenderer.hpp>
#include <Strake/Component/Renderer/WireFrameRenderer.hpp>
#include <Strake/Component/Script.hpp>
#include <Strake/Component/Collider/SphereCollider.hpp>
#include <Strake/Manager/LayerManager.hpp>
#include <Strake/init.hpp>

class Rotator : public Strake::Script
{
    public:
        using Strake::Script::Script;

        void awake() override {
            m_speed = 0.2f;
            r_transform = getParent().getTransform();
        }

        void fixedUpdate() override {
            getTransform().rotateLocal(glm::vec3(0.0f, 0.0f, m_speed));
        }

    private:
        std::optional<std::reference_wrapper<Strake::Transform>> r_transform;
        Strake::Transform &getTransform() { return r_transform.value().get(); }

        float m_speed;
};

class Scaler : public Strake::Script
{
    public:
        Scaler(Strake::GameObject &parent) :
            Script(parent),
            r_transform(parent.getTransform())
        {
        }

        void fixedUpdate() override {
            if (r_transform.getLocalScale().x > 2.0f) {
                m_scaleFactor = 0.999f;
            }
            if (r_transform.getLocalScale().x < 0.5f) {
                m_scaleFactor = 1.001f;
            }
            r_transform.scaleLocal(glm::vec3(m_scaleFactor, 1.000f, m_scaleFactor));
        }

    private:
        float m_scaleFactor = 1.001f;
        Strake::Transform &r_transform;
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
            if (Strake::EventHandler::isKeyHeld(Strake::Key::W)) {
                transform.translateLocal(glm::vec3(0.0f, 0.0f, m_speed * Strake::Time::getDeltaTime()));
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
            float yaw = mouse.x / 10.0f;
            float roll = mouse.y / 10.0f;
            transform.setLocalRotation(glm::vec3(-roll, -yaw, 0.0f));
        }
    private:
        std::optional<std::reference_wrapper<Strake::Transform>> transform;
        const float m_speed = 10.0f;
};

void printObject(Strake::GameObject &go, int depth)
{
    for (int i = 0; i < depth; i++) {
        std::cout << "\t";
    }
    std::cout << "* " << go.getName() << " {" << "\n";
    for (int i = 0; i < depth; i++) {
        std::cout << "\t";
    }
    std::cout << "\t" << "Layer: " << go.getLayer().getName() << "\n";
    auto &comp = go.getComponents();
    for (auto &c : comp) {
        for (int i = 0; i < depth; i++) {
            std::cout << "\t";
        }
        std::cout << "\t- " << c.first.name() << "\n";
    }
    auto &children = go.getChildren();
    for (auto &child : children) {
        printObject(*child.second, depth + 1);
    }
    for (int i = 0; i < depth; i++) {
        std::cout << "\t";
    }
    std::cout << "}" << std::endl;
}

int game()
{
    GLuint error = 0;

    const int WIN_WIDTH = 1400;
    const int WIN_HEIGHT = 900;
    const int FPS = 120;

    std::cout << Strake::Config::getVersion() << std::endl;
    std::cout << Strake::Config::getGLFWVersion() << std::endl;

    Strake::Application app(
        "Strake Engine V" + Strake::Config::getVersion(),
        WIN_WIDTH, WIN_HEIGHT,
        FPS
    );
    app.getWindow().setBgColor(glm::vec4(0.0f, 0.0f, 255.0f, 1.0f));
    app.getLayerManager().getLayer(0).setName("Background");
    app.getLayerManager().getLayer(1).setName("World");
    app.getLayerManager().getLayer(2).setName("UI");

    //// SCENE ////

    Strake::Scene &scene = app.getSceneManager().addScene("Main Scene");

    //// TEXTURES ////

    Strake::Texture &barelTexture = app.getTextureManager().addTexture<Strake::Texture2D>("barel", "../assets/map.png");
    Strake::Material &barelMaterial = app.getMaterialManager().addMaterial("barel");
    barelMaterial.addTexture(barelTexture, "textureSampler");

    Strake::Texture &metalTexture = app.getTextureManager().addTexture<Strake::Texture2D>("metal", "../assets/metal.png");
    Strake::Material &metalMaterial = app.getMaterialManager().addMaterial("metal");
    metalMaterial.addTexture(metalTexture, "textureSampler");
    metalMaterial.setShininess(256.0f);

    Strake::Texture &grassTexture = app.getTextureManager().addTexture<Strake::Texture2D>("grass", "../assets/grass.png");
    Strake::Material &grassMaterial = app.getMaterialManager().addMaterial("grass");
    grassMaterial.addTexture(grassTexture, "textureSampler");
    grassMaterial.setShininess(10.0f);

    Strake::Texture &treeTexture = app.getTextureManager().addTexture<Strake::Texture2D>("tree", "../assets/tree/textures/tree.png");
    Strake::Material &treeMaterial = app.getMaterialManager().addMaterial("tree");
    treeMaterial.addTexture(treeTexture, "textureSampler");

    //// GAME OBJECTS ////

    Strake::GameObject &floor = scene.addGameObject("Floor", "World");
    floor.addComponent<Strake::Plane>();
    floor.getTransform().setLocalScale(glm::vec3(20.0f, 1.0f, 20.0f));
    floor.getTransform().setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    floor.addComponent<Strake::MeshRenderer>(grassMaterial);

    Strake::GameObject &player = scene.addGameObject("Main Camera", "World");
    player.addComponent<Strake::Camera>();
    Strake::Camera &cam = player.getComponent<Strake::Camera>();
    cam.setProjection(45.0f, static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT), 0.1f, 100.0f);
    player.getTransform().setLocalPosition(glm::vec3(0.0f, 2.0f, 5.0f));
    player.addComponent<CharacterController>();
    scene.setMainCamera(cam);

    std::pair<Strake::GameObject &, std::vector<std::reference_wrapper<Strake::GameObject>>> objects = scene.loadFromFile("../assets/barrel.obj");
    objects.first.setLayer("World");
    objects.first.getTransform().setLocalPosition(glm::vec3(3.0f, 0.0f, 4.0f));
    objects.first.addComponent<Strake::MeshRenderer>(barelMaterial);
    objects.first.addComponent<Strake::SphereCollider>();
    objects.first.addComponent<Strake::WireFrameRenderer>(objects.first.getComponent<Strake::SphereCollider>());

    Strake::GameObject &barrel2 = scene.addGameObject("Barrel2", "World");
    barrel2.getTransform().setLocalPosition(glm::vec3(-3.0f, 0.0f, -4.0f));
    barrel2.addComponent<Strake::MeshFilter>();
    barrel2.getComponent<Strake::MeshFilter>().loadFromFile("../assets/barrel.obj", 0); // load the first mesh directly in the game object
    barrel2.addComponent<Strake::MeshRenderer>(barelMaterial);
    Strake::GameObject &wires = barrel2.addChild("WireFrame");
    wires.setLayer("UI");
    wires.addComponent<Strake::WireFrameRenderer>(barrel2.getComponent<Strake::MeshFilter>());
    Strake::WireFrameRenderer &renderer = wires.getComponent<Strake::WireFrameRenderer>();
    renderer.setLineWidth(0.5f);
    renderer.setLineColor(glm::vec3(1.0f, 0.0f, 0.0f));

    Strake::GameObject &sphere = scene.addGameObject("Sphere", "World");
    sphere.getTransform().setLocalPosition(glm::vec3(-3.0f, 0.5f, 4.0f));
    sphere.addComponent<Strake::Sphere>();
    sphere.addComponent<Strake::MeshRenderer>(metalMaterial);
    //sphere.addComponent<Strake::WireFrameRenderer>();

    Strake::GameObject &capsule = scene.addGameObject("Capsule", "World");
    capsule.getTransform().setLocalPosition(glm::vec3(-5.0f, 1.0f, 5.0f));
    capsule.addComponent<Strake::Capsule>();
    capsule.addComponent<Strake::MeshRenderer>(metalMaterial);

    Strake::GameObject &metalBox = scene.addGameObject("Metal Box", "UI");
    metalBox.getTransform().setLocalPosition(glm::vec3(4.0f, 0.5f, -3.0f));
    metalBox.addComponent<Strake::Cube>();
    metalBox.addComponent<Strake::MeshRenderer>(metalMaterial);

    Strake::GameObject &Moon = scene.addGameObject("Moon", "World");
    Moon.getTransform().setLocalRotation(glm::vec3(0.0f, 0.0f, 180.0f));
    Moon.addComponent<Rotator>();

    Strake::GameObject &light = Moon.addChild("Light");
    light.addComponent<Strake::PointLight>();
    light.getTransform().setLocalPosition(glm::vec3(0.0f, 30.0f, 0.0f));
    light.getComponent<Strake::PointLight>().setIntensity(0.5f);
    light.getComponent<Strake::PointLight>().setColor(glm::vec3(0.1f, 0.1f, 1.0f));

    Strake::GameObject &sun = scene.addGameObject("Sun", "World");
    sun.addComponent<Rotator>();
    sun.addComponent<Strake::DirectionalLight>();
    sun.getComponent<Strake::DirectionalLight>().setIntensity(1.0f);
    sun.getComponent<Strake::DirectionalLight>().getCullingMask().removeLayer("UI");
    sun.getComponent<Strake::DirectionalLight>().setColor(glm::vec3(1.0f, 1.0f, 0.1f));

    Strake::GameObject &tree = scene.addGameObject("Tree", "World");
    tree.addComponent<Strake::MeshFilter>();
    tree.getComponent<Strake::MeshFilter>().loadFromFile("../assets/tree/source/tree.obj"); // auto detect as one mesh (no children)
    tree.addComponent<Strake::MeshRenderer>(treeMaterial);

    for (auto &go : scene.getGameObjects()) {
        printObject(*go.second, 0);
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