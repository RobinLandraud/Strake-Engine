#include <Strake/Layer/Layer.hpp>

namespace Strake
{
    Layer::Layer() :
        m_name(""),
        m_priority(0),
        m_bitMask(1 << 0)
    {
    }

    Layer::Layer(const std::string &name, int priority) :
        m_name(name),
        m_priority(priority),
        m_bitMask(1 << priority)
    {
    }

    [[nodiscard]] std::string Layer::getName() const
    {
        return m_name;
    }

    [[nodiscard]] int Layer::getPriority() const
    {
        return m_priority;
    }

    [[nodiscard]] int Layer::getBitMask() const
    {
        return m_bitMask;
    }

    void Layer::setName(const std::string &&name)
    {
        m_name = std::move(name);
    }

    void Layer::setPriority(int priority)
    {
        m_priority = priority;
        m_bitMask = 1 << priority;
    }
}