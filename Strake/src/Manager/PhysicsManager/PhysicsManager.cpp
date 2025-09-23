#include <Strake/Manager/PhysicsManager/PhysicsManager.hpp>

namespace Strake {
    PhysicsManager::PhysicsManager(EventDispatcher &eventDispatcher) :
        m_colliderManager(eventDispatcher)
    {
    }

    void PhysicsManager::physicsUpdate()
    {
        m_colliderManager.physicsUpdate();
    }
}