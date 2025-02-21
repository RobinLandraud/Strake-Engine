#include <Strake/Manager/LayerManager.hpp>

namespace Strake
{
    LayerManager::LayerManager(EventDispatcher &eventDispatcher) :
        m_layers(),
        m_eventDispatcher(eventDispatcher)
    {
        for (int i = 0; i < 32; i++)
        {
            m_layers[i].setName("Layer " + std::to_string(i));
            m_layers[i].setPriority(i);
        }

        m_subscriptions[eventDispatcher.subscribe("setLayerByName", [&](const Event &event) {
            std::pair<std::string, GameObject &> &pair = static_cast<const EventData<std::pair<std::string, GameObject &>> &>(event).getValue();
            for (auto &layer : m_layers)
            {
                if (layer.getName() == pair.first)
                {
                    pair.second.setLayer(layer, false);
                    return;
                }
            }
        })] = "setLayerByName";

        m_subscriptions[eventDispatcher.subscribe("setLayerByPriority", [&](const Event &event) {
            std::pair<int, GameObject &> &pair = static_cast<const EventData<std::pair<int, GameObject &>> &>(event).getValue();
            pair.second.setLayer(m_layers[pair.first]);
        })] = "setLayerByPriority";
    }

    LayerManager::~LayerManager()
    {
    }

    Layer &LayerManager::getLayer(const std::string &name)
    {
        for (int i = 0; i < 32; i++)
        {
            if (m_layers[i].getName() == name)
            {
                return m_layers[i];
            }
        }
        throw std::runtime_error("Layer not found");
    }

    Layer &LayerManager::getLayer(int priority)
    {
        return m_layers[priority];
    }
}