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
            r_transform = getParent().getComponent<ECS::Transform>();
        }
        void fixedUpdate() override {
            r_transform->get().rotate(glm::vec3(0.012f, 0.010f, 0.008f));
        }
    private:
        std::optional<std::reference_wrapper<ECS::Transform>> r_transform;
};

class PlaneScaler : public ECS::Script
{
    public:
        using ECS::Script::Script;
        void awake() override {
            r_transform = getParent().getComponent<ECS::Transform>();
        }
        void fixedUpdate() override {
            ECS::Transform &transform = r_transform.value();
            if (transform.getScale().y > 3.0f) {
                m_scaleFactor = 0.999f;
            }
            if (transform.getScale().y < 1.0f) {
                m_scaleFactor = 1.001f;
            }
            transform.scale(glm::vec3(1.000f, m_scaleFactor, 1.000f));
        }
    private:
        float m_scaleFactor = 1.001f;
        std::optional<std::reference_wrapper<ECS::Transform>> r_transform;
};

int main()
{
    GLuint error = 0;

    std::cout << ECS::Config::getVersion() << std::endl;
    std::cout << ECS::Config::getGLFWVersion() << std::endl;

    ECS::Window window(1000, 800, "Strake Engine V0.1.0");
    ECS::init();
    window.setBgColor(glm::vec4(0.0f, 0.0f, 255.0f, 1.0f));
    ECS::EventHandler::init(window);

    ECS::Scene scene;

    ECS::GameObject &mainCamera = scene.addGameObject("Main Camera");
    mainCamera.addComponent<ECS::Camera>();
    ECS::Camera &cam = mainCamera.getComponent<ECS::Camera>();
    cam.setProjection(45.0f, 1000.0f / 800.0f, 0.1f, 100.0f);
    cam.setPosition(glm::vec3(0.0f, 0.0f, 6.0f));
    scene.setMainCamera(cam);

    ECS::GameObject &planeObject = scene.addGameObject("Plane");
    planeObject.addComponent<ECS::Transform>();
    planeObject.getComponent<ECS::Transform>().setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    planeObject.addComponent<ECS::Cube>();
    ECS::MeshFilter &meshFilter = planeObject.getComponent<ECS::MeshFilter>();
    planeObject.addComponent<PlaneRotator>();
    planeObject.addComponent<PlaneScaler>(); // 0 beacause several Script components can be added
    planeObject.addComponent<ECS::MeshFilter>(); // -1 because MeshFilter is already added
    planeObject.addComponent<PlaneRotator>(); // -1 because PlaneRotator is already added

    ECS::Texture2D texture("tests/stacking/sprites/gradient.png");
    if (!texture.isLoaded()) {
        std::cout << "Failed to load texture" << std::endl;
    }

    ECS::Material material;
    material.addTexture(texture, "textureSampler");
    planeObject.addComponent<ECS::MeshRenderer>(material);

    scene.awake();
    scene.start();

    ECS::Loop loop(120);
    loop.run(window, scene, true);

    ECS_EXIT();
}