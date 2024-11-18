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
#include <array>
#include <iostream>

#define ECS_EXIT() { glfwTerminate(); exit(0); }

class PlaneRotator : public ECS::Script
{
    public:
        using ECS::Script::Script;
        void update() override {
            getParent().getComponent<ECS::Transform>().rotate(glm::vec3(0.012f, 0.010f, 0.008f));
        }
};

int main()
{
    GLuint error = 0;

    std::cout << ECS::Config::getVersion() << std::endl;
    std::cout << ECS::Config::getGLFWVersion() << std::endl;

    ECS::Window window(1000, 800, "Strake Engine V0.1.0");
    ECS::init();
    ECS::Scene scene;

    ECS::GameObject &mainCamera = scene.addGameObject("Main Camera");
    mainCamera.addComponent<ECS::Camera>();
    mainCamera.getComponent<ECS::Camera>().setProjection(45.0f, 1000.0f / 800.0f, 0.1f, 100.0f);
    mainCamera.getComponent<ECS::Camera>().setPosition(glm::vec3(0.0f, 0.0f, 6.0f));
    scene.setMainCamera(mainCamera.getComponent<ECS::Camera>());

    ECS::GameObject &planeObject = scene.addGameObject("Plane");
    planeObject.addComponent<ECS::Transform>();
    planeObject.getComponent<ECS::Transform>().setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    planeObject.addComponent<ECS::MeshFilter>();
    planeObject.getComponent<ECS::MeshFilter>().setVertices({
        // Front face
        glm::vec3(-0.5f, -0.5f,  0.5f), // bottom left
        glm::vec3( 0.5f, -0.5f,  0.5f), // bottom right
        glm::vec3( 0.5f,  0.5f,  0.5f), // top right
        glm::vec3(-0.5f,  0.5f,  0.5f), // top left

        // Back face
        glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left
        glm::vec3( 0.5f, -0.5f, -0.5f), // bottom right
        glm::vec3( 0.5f,  0.5f, -0.5f), // top right
        glm::vec3(-0.5f,  0.5f, -0.5f), // top left

        // Left face
        glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left
        glm::vec3(-0.5f, -0.5f,  0.5f), // bottom right
        glm::vec3(-0.5f,  0.5f,  0.5f), // top right
        glm::vec3(-0.5f,  0.5f, -0.5f), // top left

        // Right face
        glm::vec3( 0.5f, -0.5f, -0.5f), // bottom left
        glm::vec3( 0.5f, -0.5f,  0.5f), // bottom right
        glm::vec3( 0.5f,  0.5f,  0.5f), // top right
        glm::vec3( 0.5f,  0.5f, -0.5f), // top left

        // Top face
        glm::vec3(-0.5f,  0.5f, -0.5f), // bottom left
        glm::vec3( 0.5f,  0.5f, -0.5f), // bottom right
        glm::vec3( 0.5f,  0.5f,  0.5f), // top right
        glm::vec3(-0.5f,  0.5f,  0.5f), // top left

        // Bottom face
        glm::vec3(-0.5f, -0.5f, -0.5f), // bottom left
        glm::vec3( 0.5f, -0.5f, -0.5f), // bottom right
        glm::vec3( 0.5f, -0.5f,  0.5f), // top right
        glm::vec3(-0.5f, -0.5f,  0.5f)  // top left
    });

    planeObject.getComponent<ECS::MeshFilter>().setNormals({
        // Front face
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),

        // Back face
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),

        // Left face
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),

        // Right face
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),

        // Top face
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),

        // Bottom face
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f)
    });

    planeObject.getComponent<ECS::MeshFilter>().setUVs({
        // Front face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // Back face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // Left face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // Right face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // Top face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // Bottom face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f)
    });

    planeObject.getComponent<ECS::MeshFilter>().setIndices({
        // Front face (CCW)
        0, 1, 2,
        2, 3, 0,

        // Back face (CW)
        4, 6, 5,
        6, 4, 7,

        // Left face (CCW)
        8, 9, 10,
        10, 11, 8,

        // Right face (CCW)
        13, 12, 14,
        15, 14, 12,

        // Top face (CCW)
        17, 16, 18,
        19, 18, 16,

        // Bottom face (CCW)
        20, 21, 22,
        22, 23, 20
    });
    planeObject.addComponent<PlaneRotator>();

    ECS::Texture2D texture("tests/stacking/sprites/cube.jpg");
    if (!texture.isLoaded()) {
        std::cout << "Failed to load texture" << std::endl;
    }

    ECS::Material material;
    material.addTexture(texture, "textureSampler");
    planeObject.addComponent<ECS::MeshRenderer>(material);

    bool stop = false;

    scene.awake();
    scene.start();

    while (window.isOpen())
    {
        ECS::Window::clear();
        scene.update();
        scene.lateUpdate();
        scene.render();

        window.display();
        glfwPollEvents();
    }
    ECS_EXIT();
}