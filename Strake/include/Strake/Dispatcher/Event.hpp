#pragma once

#include <string>

namespace Strake {
    class Event {
        public:
            explicit Event(std::string &&eventType);
            virtual ~Event() = default;

            const std::string& getEventType() const;

        private:
            std::string m_eventType;
    };
}