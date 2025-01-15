#pragma once

#include <Strake/Component/Component.hpp>
#include <Strake/Dispatcher/EventDispatcher.hpp>
#include <Strake/Dispatcher/EventData.hpp>

namespace Strake
{
    class Script : public Component
    {
        public:
            Script(GameObject &parent);
            ~Script();

            virtual void awake();
            virtual void start();
            virtual void update();
            virtual void fixedUpdate();
            virtual void lateUpdate();
    };
}