#include <ECS/Config.hpp>
#include <ECS/Component.hpp>
#include <ECS/Loop.hpp>
#include <iostream>
//#include <ECS/Config.hpp>


// opengl
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

int init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glDepthFunc(GL_LEQUAL); // Set depth function to less than or equal to 
    glEnable(GL_TEXTURE_2D); // Enable texturing
    glEnable(GL_BLEND); // Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function to use alpha values
    glFrontFace(GL_CCW); // Front faces are counter-clockwise
    glEnable(GL_CULL_FACE); // Enable face culling
    glCullFace(GL_BACK); // Cull back faces
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the clear color to black
    glEnable(GL_ALPHA_TEST); // Enable alpha testing
    glAlphaFunc(GL_GREATER, 0.1f); // Render pixels with alpha greater than 0.1
    return 0;
}

int main()
{
    ECS::GameObject gameObject("GameObject");
    gameObject.addComponent<TestComponent>();
    auto comp = gameObject.getComponent<TestComponent>();
    if (comp.has_value()) {
        ECS::Component &testComponent = comp.value().get();
        testComponent.awake();
    }

    ECS::Window window(800, 600, "Window");
    ECS::Loop loop(60);
    loop.run(window);

    return 0;
}