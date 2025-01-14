#pragma once

#include <ECS/Dispatcher/Event.hpp>

namespace Strake {
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
}