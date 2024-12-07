#include <ECS/Camera.hpp>
#include <ECS/Component.hpp>
#include <ECS/Config.hpp>
#include <ECS/Loop.hpp>
#include <ECS/Script.hpp>
#include <ECS/Shaders.hpp>
#include <ECS/Material.hpp>
#include <ECS/Transform.hpp>
#include <ECS/MeshFilter.hpp>
#include <ECS/MeshRenderer.hpp>
#include <ECS/init.hpp>
#include <ECS/Scene.hpp>
#include <ECS/EventHandler.hpp>
#include <array>
#include <iostream>

#define ECS_EXIT() { glfwTerminate(); exit(0); }

class PlaneRotator : public ECS::Script
{
    public:
        using ECS::Script::Script;
        void awake() override {
            r_transform = getParent().getTransform();
        }
        void fixedUpdate() override {
            r_transform->get().rotate(glm::vec3(1.2f, 1.0f, 0.8f));
        }
    private:
        std::optional<std::reference_wrapper<ECS::Transform>> r_transform;
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
            if (transform.getScale().x > 2.0f) {
                m_scaleFactor = 0.999f;
            }
            if (transform.getScale().x < 1.0f) {
                m_scaleFactor = 1.001f;
            }
            transform.scale(glm::vec3(m_scaleFactor, 1.000f, m_scaleFactor));
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
            r_cam = getParent().findComponent<ECS::Camera>();
        }
        void update() override {
            ECS::Camera &cam = r_cam.value();
            const ECS::mouse_t &mouse = ECS::EventHandler::getMouse();
            //std::cout << "Mouse: " << mouse.x << " " << mouse.y << std::endl;
            if (ECS::EventHandler::isKeyHeld(ECS::Key::W)) {
                cam.translate(glm::vec3(0.0f, 0.0f, m_speed));
                //std::cout << "Z key pressed" << std::endl;
            } else if (ECS::EventHandler::isKeyHeld(ECS::Key::S)) {
                cam.translate(glm::vec3(0.0f, 0.0f, -m_speed));
            }
            if (ECS::EventHandler::isKeyHeld(ECS::Key::A)) {
                cam.translate(glm::vec3(-m_speed, 0.0f, 0.0f));
            } else if (ECS::EventHandler::isKeyHeld(ECS::Key::D)) {
                cam.translate(glm::vec3(m_speed, 0.0f, 0.0f));
            }
            if (ECS::EventHandler::isKeyHeld(ECS::Key::Space)) {
                cam.translate(glm::vec3(0.0f, m_speed, 0.0f));
            } else if (ECS::EventHandler::isKeyHeld(ECS::Key::LeftShift)) {
                cam.translate(glm::vec3(0.0f, -m_speed, 0.0f));
            }
            //look at mouse
            cam.setPitch(-mouse.x * 0.1f);
            cam.setRoll(-mouse.y * 0.1f);
            //setmouse to center
            //std::cout << "Camera Rotation: " << cam.getRotation().x << " " << cam.getRotation().y << " " << cam.getRotation().z << std::endl;
        }
    private:
        std::optional<std::reference_wrapper<ECS::Camera>> r_cam;
        std::optional<std::reference_wrapper<ECS::Transform>> transform;
        const float m_speed = 0.05f;
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

int main()
{
    GLuint error = 0;

    std::cout << ECS::Config::getVersion() << std::endl;
    std::cout << ECS::Config::getGLFWVersion() << std::endl;

    ECS::Window window(1000, 800, "Strake Engine V0.1.0");
    ECS::init();
    window.setBgColor(glm::vec4(0.0f, 0.0f, 255.0f, 1.0f));

    // create singletons
    ECS::EventHandler::init(window);
    ECS::Time::init();

    ECS::Scene scene;

    ECS::GameObject &player = scene.addGameObject("Main Camera");
    player.addComponent<ECS::Camera>();
    ECS::Camera &cam = player.getComponent<ECS::Camera>();
    cam.setProjection(45.0f, 1000.0f / 800.0f, 0.1f, 100.0f);
    cam.setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    player.addComponent<CharacterController>();
    scene.setMainCamera(cam);

    ECS::GameObject &planeObject = scene.addGameObject("Plane");
    planeObject.getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    //planeObject.addComponent<ECS::Cube>();
    planeObject.addComponent<ECS::MeshFilter>();
    planeObject.getComponent<ECS::MeshFilter>().loadFromOBJ("assets/barrel.obj");
    ECS::MeshFilter &meshFilter = planeObject.getComponent<ECS::MeshFilter>();
    planeObject.addComponent<PlaneRotator>();
    std::cout << planeObject.addComponent<PlaneScaler>() << std::endl;

    ECS::Texture2D texture("assets/map.png");
    if (!texture.isLoaded()) {
        std::cout << "Failed to load texture" << std::endl;
    }

    ECS::Material material;
    material.addTexture(texture, "textureSampler");
    planeObject.addComponent<ECS::MeshRenderer>(material);

    for (auto &go : scene.getGameObjects()) {
        printComponent(*go.second, 0);
    }

    scene.awake();
    scene.start();

    ECS::Loop loop(100);
    loop.run(window, scene, true);

    //destroy singletons
    ECS::EventHandler::destroy();
    ECS::Time::destroy();

    ECS_EXIT();
}