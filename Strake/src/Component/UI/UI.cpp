#include <Strake/Component/UI/UI.hpp>

namespace Strake
{
    UI::UI(GameObject &parent)
        : Component(parent)
    {
        setDerivedType(typeid(UI));
    }

    UI::~UI()
    {
    }
}