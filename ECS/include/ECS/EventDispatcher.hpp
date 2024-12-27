#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <mutex>

#include <iostream>

namespace ECS {

    class Event {
        public:
            explicit Event(std::string &&eventType);
            virtual ~Event() = default;

            const std::string& getEventType() const;

        private:
            std::string m_eventType;
    };

    template <typename T>
    class EventData : public Event {
        public:
            EventData(T &value, std::string &&eventType) :
                Event(std::move(eventType)),
                m_value(value)
            {}

            [[nodiscard]] T &getValue() const {
                return m_value.get();
            }

        private:
            std::reference_wrapper<T> m_value;
    };

    class EventDispatcher {
        public:
            EventDispatcher() = default;
            ~EventDispatcher() = default;
            using Callback = std::function<void(const Event&)>;
            
            void subscribe(const std::string& eventType, Callback callback);
            void broadcast(const Event& event);

        private:
            std::unordered_map<std::string, std::vector<Callback>> subscribers;
            mutable std::mutex mtx;
    };
}