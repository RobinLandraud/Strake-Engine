#include <ECS/Loop.hpp>
#include <iostream>
#include <ECS/EntityManager.hpp>
#include <ECS/Config.hpp>
//#include <ECS/Config.hpp>

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
        void awake() {
            test += 1;
            std::cout << "TestComponent awake" << std::endl;
        }
        void destroyParent() {
            std::cout << "Destroying parent : " + m_parent << std::endl;
            r_entities.erase(m_parent);
        }
    private:
        int test = 0;
};

int main()
{
    std::cout << "ECS version: " << ECS::Config::getVersion() << std::endl;
    std::cout << "SFML version: " << ECS::Config::getSFMLVersion() << std::endl;

    ECS::EntityManager manager;
    manager.addEntity("Entity");
    manager.addComponent<TestComponent>("Entity", "TestComponent");
    auto component = manager.getComponent<TestComponent>("Entity", "TestComponent");
    if (component.has_value())
        component.value().get().destroyParent();
    auto components = manager.getComponents("Entity");
    if (!components.has_value())
        std::cout << "Components not found" << std::endl;

    ECS::Window window(800, 600, "Window");
    ECS::Loop loop(60);
    loop.run(window);

    return 0;
}