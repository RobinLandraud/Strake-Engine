#pragma once

#include <Strake/Manager/PhysicsManager/ColliderManager.hpp>
#include <Strake/Dispatcher/EventDispatcher.hpp>

namespace Strake {
    class PhysicsManager {
        public:
            explicit PhysicsManager(EventDispatcher &eventDispatcher);
            ~PhysicsManager() = default;
            PhysicsManager(const PhysicsManager &other) = delete;
            PhysicsManager(PhysicsManager &&other) = delete;
            PhysicsManager &operator=(const PhysicsManager &other) = delete;
            PhysicsManager &operator=(PhysicsManager &&other) = delete;

        private:
            ColliderManager m_colliderManager;
    };
}