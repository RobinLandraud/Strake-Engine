#include <ECS/Script.hpp>

namespace ECS
{
    Script::Script(GameObject &parent) : Component(parent)
    {
        setDerivedType(typeid(Script));
    }
}