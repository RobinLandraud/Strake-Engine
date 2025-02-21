#pragma once

#include <Strake/Layer/Layer.hpp>
#include <Strake/GameObject/GameObject.hpp>
#include <Strake/Dispatcher/EventDispatcher.hpp>
#include <Strake/Dispatcher/EventData.hpp>
#include <array>
#include <optional>
#include <unordered_map>
#include <stdexcept>

namespace Strake {
    class LayerManager {
    public:
        LayerManager(EventDispatcher &eventDispatcher);
        ~LayerManager();
        Layer &getLayer(const std::string &name);
        Layer &getLayer(int priority);

    private:
        std::array<Layer, 32> m_layers;

        EventDispatcher &m_eventDispatcher;
        std::unordered_map<EventDispatcher::EventID, std::string> m_subscriptions;
    };
}