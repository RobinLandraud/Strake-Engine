#include <Strake/Script/Script.hpp>

namespace Strake
{
    Script::Script(GameObject &parent) : Component(parent)
    {
        setDerivedType(typeid(Script));
        EventData<Script> eventData(*this, "addScript");
        parent.getEventDispatcher().broadcast(eventData);
    }

    Script::~Script()
    {
        EventData<Script> eventData(*this, "removeScript");
        getParent().getEventDispatcher().broadcast(eventData);
    }

    void Script::awake()
    {
    }

    void Script::start()
    {
    }

    void Script::update()
    {
    }

    void Script::fixedUpdate()
    {
    }

    void Script::lateUpdate()
    {
    }
}