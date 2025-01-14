#pragma once

#include <ECS/Dispatcher/Event.hpp>
#include <functional>
#include <unordered_map>
#include <mutex>

namespace Strake {
    class EventDispatcher {
        public:
            EventDispatcher() = default;
            ~EventDispatcher() = default;
            using EventID = size_t;
            using Callback = std::function<void(const Event&)>;
            
            EventID subscribe(const std::string& eventType, Callback callback);
            void unsubscribe(const std::string& eventType, EventID id);
            void broadcast(const Event& event);

        private:
            std::unordered_map<std::string, std::vector<std::pair<EventID, Callback>>> m_subscribers;
            mutable std::mutex mtx;
            std::atomic<EventID> currentID;
    };
}