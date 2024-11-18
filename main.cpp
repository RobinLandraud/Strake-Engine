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
#include <array>
#include <iostream>

// f() const means that the function does not modify any member variables.
// const T& f() returns a reference to the object without allowing it to be modified.
// T& const f() is not a valid syntax.
// T* const f() returns a pointer to the object without allowing the pointer itself to be modified, 
// but allowing the object to be modified.
// const T f() returns a copy of the object without allowing the copy to be modified.
// const T* f() returns a pointer to the object without allowing the pointer to be modified,
// but allowing the object to be modified.
// T& f() returns a reference to the object, allowing it to be modified.
// T* f() returns a pointer to the object, allowing it to be modified and allowing the pointer to be modified to point to something else.
// T&& f() returns an rvalue reference to the object, allowing it to be modified (transfers ownership of the object).
// const T&& f() is not a valid syntax; you cannot have `const` with `&&` as it does not make sense in C++.
// T&& const f() is also not a valid syntax.

//ECS_EXIT() is a macro that calls glfwTerminate() and exits the program.
#define ECS_EXIT() { glfwTerminate(); exit(0); }

void createSquareVAO(GLuint &vao, GLuint &vbo)
{
    std::array<float, 30> vertices = {
        // Positions        // Texture Coords
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f,

        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Texture Coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

class TestComponent : public ECS::Component
{
    public:
        using ECS::Component::Component;
        void awake() override {
            test += 1;
            std::cout << "TestComponent awake" << std::endl;
            std::cout << getParent().getName() << std::endl;
            auto testComponent = getParent().getComponent<TestComponent>();
            std::cout << testComponent.test << std::endl;
        }
    private:
        int test = 0;
};

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

    ECS::GameObject mainCamera("Main Camera");
    mainCamera.addComponent<ECS::Camera>();
    mainCamera.getComponent<ECS::Camera>().setProjection(45.0f, 1000.0f / 800.0f, 0.1f, 100.0f);
    mainCamera.getComponent<ECS::Camera>().setPosition(glm::vec3(0.0f, 0.0f, 6.0f));

    ECS::GameObject planeObject("plane");
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


    ECS::ShaderProgram shaderProgram("ECS/src/Shader/glsl/texture2D/vertex.glsl", "ECS/src/Shader/glsl/texture2D/fragment.glsl");
    ECS::Material material(shaderProgram);
    material.addTexture(texture, "textureSampler");
    planeObject.addComponent<ECS::MeshRenderer>(material);
    shaderProgram.use();

    //ECS::Loop loop(60);
    //loop.run(window);

    GLuint vao = 0;
    GLuint vbo = 0;
    createSquareVAO(vao, vbo);

    bool stop = false;

    while (window.isOpen())
    {
        ECS::Window::clear();

        planeObject.getComponent<PlaneRotator>().update();
        planeObject.getComponent<ECS::Transform>().lateUpdate();
        mainCamera.getComponent<ECS::Camera>().lateUpdate();

        shaderProgram.setUniform("model", planeObject.getComponent<ECS::Transform>().getMatrix());
        shaderProgram.setUniform("projection", mainCamera.getComponent<ECS::Camera>().getProjectionMatrix());
        shaderProgram.setUniform("view", mainCamera.getComponent<ECS::Camera>().getViewMatrix());

        //glBindVertexArray(vao);
        //
        //error = glGetError();
        //if (error != GL_NO_ERROR) {
        //    std::cout << "Error bind vertex array: " << error << std::endl;
        //}
        //glDrawArrays(GL_TRIANGLES, 0, 6);  // Draw two triangles for the square
        //error = glGetError();
        //if (error != GL_NO_ERROR) {
        //    std::cout << "Error draw arrays: " << error << std::endl;
        //}
//
        //glBindVertexArray(0);
        planeObject.getComponent<ECS::MeshRenderer>().render();

        window.display();
        glfwPollEvents();
    }
    ECS_EXIT();
    return 0;
}