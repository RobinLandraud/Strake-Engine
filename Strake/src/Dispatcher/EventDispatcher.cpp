#include <Strake/Dispatcher/EventDispatcher.hpp>

namespace Strake {
    EventDispatcher::EventID EventDispatcher::subscribe(const std::string& eventType, Callback callback) {
        std::lock_guard<std::mutex> lock(mtx);
        m_subscribers[eventType][currentID] = callback;
        return currentID - 1;
    }

    void EventDispatcher::unsubscribe(const std::string& eventType, EventID id) {
        std::lock_guard<std::mutex> lock(mtx);
        auto subs = m_subscribers.find(eventType);
        if (subs == m_subscribers.end()) {
            return;
        }
        auto it = subs->second.find(id);
        if (it != subs->second.end()) {
            subs->second.erase(it);
            if (subs->second.empty()) {
                m_subscribers.erase(subs);
            }
        }
    }

    void EventDispatcher::broadcast(const Event& event) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = m_subscribers.find(event.getEventType());
        if (it != m_subscribers.end()) {
            for (const auto& [_, callback] : it->second) {
                callback(event);
            }
        }
    }

}