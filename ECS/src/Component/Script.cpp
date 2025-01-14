#include <ECS/Script/Script.hpp>

namespace Strake
{
    Script::Script(GameObject &parent) : Component(parent)
    {
        setDerivedType(typeid(Script));
    }
}