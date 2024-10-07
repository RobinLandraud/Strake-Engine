#include <ECS/Loop.hpp>
#include <iostream>
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

int main()
{
    //std::cout << "ECS version: " << ECS::Config::getVersion() << std::endl;
    //std::cout << "SFML version: " << ECS::Config::getSFMLVersion() << std::endl;
    ECS::Window window(800, 600, "Window");
    ECS::Loop loop(60);
    loop.run(window);

    return 0;
}