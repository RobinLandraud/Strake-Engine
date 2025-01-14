#include <ECS/Dispatcher/EventDispatcher.hpp>

namespace Strake {
    EventDispatcher::EventID EventDispatcher::subscribe(const std::string& eventType, Callback callback) {
        std::lock_guard<std::mutex> lock(mtx);
        m_subscribers[eventType].push_back(std::pair(currentID++, callback));
        return currentID - 1;
    }

    void EventDispatcher::unsubscribe(const std::string& eventType, EventID id) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = m_subscribers.find(eventType);
        if (it != m_subscribers.end()) {
            it->second.erase(std::remove_if(it->second.begin(), it->second.end(), [id](const std::pair<EventID, Callback>& pair) {
                return pair.first == id;
            }), it->second.end());
        }
        if (it->second.empty()) {
            m_subscribers.erase(it);
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