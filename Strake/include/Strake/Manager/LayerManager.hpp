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
        LayerManager();
        ~LayerManager();
        [[nodiscard]] Layer &getLayer(const std::string &name);
        [[nodiscard]] Layer &getLayer(int priority);
        [[nodiscard]] const Layer &getLayer(const std::string &name) const;
        [[nodiscard]] const Layer &getLayer(int priority) const;

    private:
        std::array<Layer, 32> m_layers;

        std::unordered_map<EventDispatcher::EventID, std::string> m_subscriptions;
    };
}