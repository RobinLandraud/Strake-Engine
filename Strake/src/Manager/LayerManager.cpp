#include <Strake/Manager/LayerManager.hpp>

namespace Strake
{
    LayerManager::LayerManager() :
        m_layers()
    {
        for (int i = 0; i < 32; i++)
        {
            m_layers[i].setName("Layer " + std::to_string(i));
            m_layers[i].setPriority(i);
        }
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

    const Layer &LayerManager::getLayer(const std::string &name) const
    {
        for (int i = 0; i < 32; i++)
        {
            if (m_layers[i].getName() == name)
            {
                return m_layers.at(i);
            }
        }
        throw std::runtime_error("Layer not found");
    }

    const Layer &LayerManager::getLayer(int priority) const
    {
        return m_layers.at(priority);
    }
}