#include <ECS/Component.hpp>
#include <ECS/Config.hpp>
#include <ECS/Loop.hpp>
#include <ECS/init.hpp>
#include <ECS/Shaders.hpp>
#include <ECS/Textures.hpp>
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
    float vertices[] = {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture Coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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
            TestComponent &testComponent = getParent().getComponent<TestComponent>().value().get();
            std::cout << testComponent.test << std::endl;
        }
    private:
        int test = 0;
};

int main()
{
    std::cout << ECS::Config::getVersion() << std::endl;
    std::cout << ECS::Config::getGLFWVersion() << std::endl;
    ECS::Window window(1000, 800, "Strake Engine V0.1.0");
    ECS::init();

    GLuint error = 0;

    ECS::GameObject gameObject("GameObject");
    gameObject.addComponent<TestComponent>();
    auto comp = gameObject.getComponent<TestComponent>();
    if (comp.has_value()) {
        ECS::Component &testComponent = comp.value().get();
        testComponent.awake();
    }

    ECS::Texture2D texture("tests/stacking/sprites/grass.png");
    if (!texture.isLoaded()) {
        std::cout << "Failed to load texture" << std::endl;
    }


    ECS::ShaderProgram shaderProgram("ECS/src/Shader/glsl/texture2D/vertex.glsl", "ECS/src/Shader/glsl/texture2D/fragment.glsl");
    shaderProgram.use();
    shaderProgram.setUniform("ourTexture", 0);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f); // Perspective projection
    shaderProgram.setUniform("projection", projection);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); // Move back along Z-axis
    shaderProgram.setUniform("view", view);
    shaderProgram.setUniform("model", glm::mat4(1.0f)); // Identity matrix for model matrix

    //ECS::Loop loop(60);
    //loop.run(window);

    GLuint vao, vbo;
    createSquareVAO(vao, vbo);

    bool stop = false;
    while (window.isOpen())
    {
        window.clear();

        shaderProgram.use();

        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "Error texture bind: " << error << std::endl;
        }
        glBindVertexArray(vao);
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "Error bind vertex array: " << error << std::endl;
        }
        glDrawArrays(GL_TRIANGLES, 0, 6);  // Draw two triangles for the square
        error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cout << "Error draw arrays: " << error << std::endl;
        }

        glBindVertexArray(0);
        texture.unbind();

        window.display();
        glfwPollEvents();
    }
    ECS_EXIT();
    return 0;
}