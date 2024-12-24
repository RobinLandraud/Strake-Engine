#include <ECS/EventDispatcher.hpp>
#include <iostream>

namespace ECS {

    Event::Event(std::string &&eventType) :
        m_eventType(std::move(eventType))
    {}

    const std::string& Event::getEventType() const {
        return m_eventType;
    }

    void EventDispatcher::subscribe(const std::string& eventType, Callback callback) {
        std::lock_guard<std::mutex> lock(mtx);
        subscribers[eventType].push_back(callback);
    }

    void EventDispatcher::broadcast(const Event& event) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = subscribers.find(event.getEventType());
        if (it != subscribers.end()) {
            for (const auto& callback : it->second) {
                callback(event);
            }
        }
    }

}