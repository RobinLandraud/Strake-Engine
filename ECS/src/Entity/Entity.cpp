#include <ECS/Entity.hpp>

namespace ECS {

    uint32_t Entity::m_idCounter = 0;

    Entity::Entity(const std::string &name)
        : m_id(m_idCounter++), m_name(name)
    {}

    const uint32_t Entity::getId() const
    {
        return m_id;
    }

    const std::string &Entity::getName() const
    {
        return m_name;
    }

    void Entity::awake()
    {
        for (auto &component : m_components)
        {
            component.second.component->awake();
        }
    }

    void Entity::start()
    {
        for (auto &component : m_components)
        {
            component.second.component->start();
        }
    }

    void Entity::update()
    {
        for (auto &component : m_components)
        {
            component.second.component->update();
        }
    }

    void Entity::fixedUpdate()
    {
        for (auto &component : m_components)
        {
            component.second.component->fixedUpdate();
        }
    }

    void Entity::lateUpdate()
    {
        for (auto &component : m_components)
        {
            component.second.component->lateUpdate();
        }
    }

    void Entity::render()
    {
        for (auto &component : m_components)
        {
            component.second.component->render();
        }
    }
}