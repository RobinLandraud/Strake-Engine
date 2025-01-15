#pragma once

#include <Strake/Script/Script.hpp>

namespace Strake {
    class ScriptManager {
        public:
            ScriptManager(EventDispatcher &eventDispatcher);
            ~ScriptManager();
            void addScript(Script &script);
            void removeScript(Script &script);

            //pipeline
            void awake();
            void start();
            void update();
            void fixedUpdate();
            void lateUpdate();
        private:
            std::vector<std::reference_wrapper<Script>> m_scripts;

            EventDispatcher &m_eventDispatcher;
            std::unordered_map<EventDispatcher::EventID, std::string> m_subscriptions;
    };
}