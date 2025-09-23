#include <Strake/Dispatcher/Event.hpp>

namespace Strake {
    Event::Event(std::string &&eventType) :
        m_eventType(std::move(eventType))
    {}

    const std::string& Event::getEventType() const {
        return m_eventType;
    }
}