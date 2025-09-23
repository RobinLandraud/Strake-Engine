#include <Strake/Manager/ScriptManager.hpp>

namespace Strake {
    ScriptManager::ScriptManager(EventDispatcher &eventDispatcher) :
        m_eventDispatcher(eventDispatcher)
    {
        m_subscriptions[m_eventDispatcher.subscribe("addScript", [this](const Event &event) {
            Script &script = static_cast<const EventData<Script> &>(event).getValue();
            addScript(script);
        })] = "addScript";

        m_subscriptions[m_eventDispatcher.subscribe("removeScript", [this](const Event &event) {
            Script &script = static_cast<const EventData<Script> &>(event).getValue();
            removeScript(script);
        })] = "removeScript";
    }

    ScriptManager::~ScriptManager()
    {
        for (const auto &[id, event] : m_subscriptions) {
            m_eventDispatcher.unsubscribe(event, id);
        }
    }

    void ScriptManager::addScript(Script &script)
    {
        m_scripts.push_back(script);
    }

    void ScriptManager::removeScript(Script &script)
    {
        auto it = std::find_if(m_scripts.begin(), m_scripts.end(),
            [&script](const std::reference_wrapper<Script>& ref) {
                return &ref.get() == &script;
            }
        );
        if (it != m_scripts.end()) {
            m_scripts.erase(it);
        }
    }

    void ScriptManager::awake()
    {
        for (auto &script : m_scripts) {
            script.get().awake();
        }
    }

    void ScriptManager::start()
    {
        for (auto &script : m_scripts) {
            script.get().start();
        }
    }

    void ScriptManager::update()
    {
        for (auto &script : m_scripts) {
            script.get().update();
        }
    }

    void ScriptManager::fixedUpdate()
    {
        for (auto &script : m_scripts) {
            script.get().fixedUpdate();
        }
    }

    void ScriptManager::lateUpdate()
    {
        for (auto &script : m_scripts) {
            script.get().lateUpdate();
        }
    }
}