#include <ECS/Camera.hpp>
#include <ECS/Component.hpp>
#include <ECS/Config.hpp>
#include <ECS/GameLoop.hpp>
#include <ECS/Script.hpp>
#include <ECS/Shaders.hpp>
#include <ECS/Material.hpp>
#include <ECS/Transform.hpp>
#include <ECS/MeshFilter.hpp>
#include <ECS/MeshRenderer.hpp>
#include <ECS/init.hpp>
#include <ECS/Scene.hpp>
#include <ECS/EventHandler.hpp>
#include <ECS/Application.hpp>
#include <array>
#include <iostream>
#include <memory>

class PlaneRotator : public ECS::Script
{
    public:
        PlaneRotator(ECS::GameObject &parent, float speed) :
            ECS::Script(parent),
            m_speed(speed)
        {

        }
        void awake() override {
            r_transform = getParent().getTransform();
        }
        void fixedUpdate() override {
            r_transform->get().rotateLocal(glm::vec3(0.0f, m_speed, 0.0f));
        }
    private:
        std::optional<std::reference_wrapper<ECS::Transform>> r_transform;
        float m_speed;
};

class PlaneScaler : public ECS::Script
{
    public:
        using ECS::Script::Script;
        void awake() override {
            r_transform = getParent().getTransform();
        }
        void fixedUpdate() override {
            ECS::Transform &transform = r_transform.value();
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
        std::optional<std::reference_wrapper<ECS::Transform>> r_transform;
};

class CharacterController: public ECS::Script
{
    public:
        using ECS::Script::Script;
        void awake() override {
            transform = getParent().getTransform();
        }
        void update() override {
            const ECS::mouse_t &mouse = ECS::EventHandler::getMouse();
            ECS::Transform &transform = this->transform.value();
            //std::cout << "Mouse: " << mouse.x << " " << mouse.y << std::endl;
            if (ECS::EventHandler::isKeyHeld(ECS::Key::W)) {
                transform.translateLocal(glm::vec3(0.0f, 0.0f, m_speed * ECS::Time::getDeltaTime()));
                //std::cout << "Z key pressed" << std::endl;
            } else if (ECS::EventHandler::isKeyHeld(ECS::Key::S)) {
                transform.translateLocal(glm::vec3(0.0f, 0.0f, -m_speed * ECS::Time::getDeltaTime()));
            }
            if (ECS::EventHandler::isKeyHeld(ECS::Key::A)) {
                transform.translateLocal(glm::vec3(-m_speed * ECS::Time::getDeltaTime(), 0.0f, 0.0f));
            } else if (ECS::EventHandler::isKeyHeld(ECS::Key::D)) {
                transform.translateLocal(glm::vec3(m_speed * ECS::Time::getDeltaTime(), 0.0f, 0.0f));
            }
            if (ECS::EventHandler::isKeyHeld(ECS::Key::Space)) {
                transform.translateLocal(glm::vec3(0.0f, m_speed * ECS::Time::getDeltaTime(), 0.0f));
            } else if (ECS::EventHandler::isKeyHeld(ECS::Key::LeftShift)) {
                transform.translateLocal(glm::vec3(0.0f, -m_speed * ECS::Time::getDeltaTime(), 0.0f));
            }
            //look at mouse
            float yaw = mouse.x;
            float roll = mouse.y;
            transform.setLocalRotation(glm::vec3(-roll, -yaw, 0.0f));
            //setmouse to center
            //std::cout << "Camera Rotation: " << transform.getLocalRotation().x << " " << transform.getLocalRotation().y << " " << transform.getLocalRotation().z << std::endl;
        }
    private:
        std::optional<std::reference_wrapper<ECS::Transform>> transform;
        const float m_speed = 10.0f;
};

void printComponent(ECS::GameObject &go, int depth)
{
    for (int i = 0; i < depth; i++) {
        std::cout << "\t";
    }
    std::cout << "* " << go.getName() << " {" << std::endl;
    auto &comp = go.getComponents();
    for (auto &c : comp) {
        for (int i = 0; i < depth; i++) {
            std::cout << "\t";
        }
        std::cout << "\t- " << c.first.name() << std::endl;
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

ECS::Scene createScene(int width, int height)
{
    return ECS::Scene();
}

int game()
{
    GLuint error = 0;

    const int WIN_WIDTH = 1400;
    const int WIN_HEIGHT = 900;

    std::cout << ECS::Config::getVersion() << std::endl;
    std::cout << ECS::Config::getGLFWVersion() << std::endl;

    ECS::Application app("Strake Engine V0.1.1", WIN_WIDTH, WIN_HEIGHT, 60);
    app.getWindow().setBgColor(glm::vec4(0.0f, 0.0f, 255.0f, 1.0f));

    ECS::Scene &scene = app.getSceneManager().addScene("Main Scene");

    ECS::GameObject &player = scene.addGameObject("Main Camera");
    player.addComponent<ECS::Camera>();
    ECS::Camera &cam = player.getComponent<ECS::Camera>();
    cam.setProjection(45.0f, static_cast<float>(WIN_WIDTH) / static_cast<float>(WIN_HEIGHT), 0.1f, 100.0f);
    player.getTransform().setLocalPosition(glm::vec3(0.0f, 2.0f, 5.0f));
    player.addComponent<CharacterController>();
    scene.setMainCamera(cam);

    ECS::GameObject &barrel = scene.addGameObject("Barrel");
    barrel.getTransform().setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    barrel.addComponent<ECS::MeshFilter>();
    barrel.getComponent<ECS::MeshFilter>().loadFromOBJ("assets/barrel.obj");
    ECS::MeshFilter &meshFilter = barrel.getComponent<ECS::MeshFilter>();
    barrel.addComponent<PlaneRotator>(1.0f);
    barrel.addComponent<PlaneScaler>();

    ECS::GameObject &light = barrel.addChild("Light");
    light.addComponent<ECS::PointLight>();
    light.getTransform().setLocalPosition(glm::vec3(5.0f, 1.0f, 5.0f));
    light.getComponent<ECS::PointLight>().setColor(glm::vec3(1.0f, 0.1f, 0.1f));

    ECS::GameObject &child = barrel.addChild("Plane Child");
    child.getTransform().setLocalPosition(glm::vec3(8.0f, 0.5f, 0.0f));
    child.addComponent<ECS::Cube>();
    child.addComponent<PlaneRotator>(1.0f);
    ECS::GameObject &childChild = child.addChild("Plane Child Child");
    childChild.getTransform().setLocalPosition(glm::vec3(2.0f, 0.0f, 0.0f));
    childChild.addComponent<ECS::Cube>();
    childChild.addComponent<PlaneRotator>(2.0f);
    ECS::GameObject &floor = scene.addGameObject("Floor");
    floor.getTransform().setLocalPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    floor.addComponent<ECS::Cube>();
    floor.getTransform().setLocalScale(glm::vec3(40.0f, 0.1f, 40.0f));

    ECS::Texture &barelTexture = app.getTextureManager().addTexture<ECS::Texture2D>("barel", "assets/map.png");
    ECS::Texture &metalTexture = app.getTextureManager().addTexture<ECS::Texture2D>("metal", "assets/metal.png");
    ECS::Texture &plasticTexture = app.getTextureManager().addTexture<ECS::Texture2D>("plastic", "assets/plastic.jpg");

    ECS::Material &barelMaterial = app.getMaterialManager().addMaterial("barel");
    barelMaterial.addTexture(barelTexture, "textureSampler");
    barelMaterial.setShininess(32.0f);

    ECS::Material &metalMaterial = app.getMaterialManager().addMaterial("metal");
    metalMaterial.addTexture(metalTexture, "textureSampler");
    metalMaterial.setShininess(256.0f);

    ECS::Material &plasticMaterial = app.getMaterialManager().addMaterial("plastic");
    plasticMaterial.addTexture(plasticTexture, "textureSampler");
    plasticMaterial.setShininess(32.0f);


    barrel.addComponent<ECS::MeshRenderer>(barelMaterial);
    child.addComponent<ECS::MeshRenderer>(metalMaterial);
    childChild.addComponent<ECS::MeshRenderer>(plasticMaterial);
    floor.addComponent<ECS::MeshRenderer>(plasticMaterial);

    for (auto &go : scene.getGameObjects()) {
        printComponent(*go.second, 0);
    }

    app.run();
    return 0;
}

int main()
{
    int out = game();
    std::cout << "Game exited with code: " << out << std::endl;
    return out;
}