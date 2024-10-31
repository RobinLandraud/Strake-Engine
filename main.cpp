#include <ECS/Component.hpp>
#include <ECS/Config.hpp>
#include <ECS/Loop.hpp>
#include <ECS/init.hpp>
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
    ECS::init();
    ECS::GameObject gameObject("GameObject");
    gameObject.addComponent<TestComponent>();
    auto comp = gameObject.getComponent<TestComponent>();
    if (comp.has_value()) {
        ECS::Component &testComponent = comp.value().get();
        testComponent.awake();
    }

    ECS::Window window(1000, 800, "Strake Engine V0.1.0");
    ECS::Loop loop(60);
    loop.run(window);

    return 0;
}