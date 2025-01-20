#include <Strake/Manager/PhysicsManager/PhysicsManager.hpp>

namespace Strake {
    PhysicsManager::PhysicsManager(EventDispatcher &eventDispatcher) :
        m_colliderManager(eventDispatcher)
    {
    }
}