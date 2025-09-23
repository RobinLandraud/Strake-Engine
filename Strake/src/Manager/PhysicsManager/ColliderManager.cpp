#include <Strake/Manager/PhysicsManager/ColliderManager.hpp>

namespace Strake {
    ColliderManager::ColliderManager(EventDispatcher &eventDispatcher) : m_eventDispatcher(eventDispatcher) {
        m_subscriptions[m_eventDispatcher.subscribe("addCollider", [this](const Event &event) {
            Collider &collider = static_cast<const EventData<Collider> &>(event).getValue();
            addCollider(collider);
        })] = "addCollider";
        m_subscriptions[m_eventDispatcher.subscribe("removeCollider", [this](const Event &event) {
            Collider &collider = static_cast<const EventData<Collider> &>(event).getValue();
            removeCollider(collider);
        })] = "removeCollider";
        m_subscriptions[m_eventDispatcher.subscribe("clearColliders", [this](const Event &event) {
            clear();
        })] = "clearColliders";
    }

    ColliderManager::~ColliderManager() {
        for (const auto &[id, event] : m_subscriptions) {
            m_eventDispatcher.unsubscribe(event, id);
        }
    }

    void ColliderManager::addCollider(Collider &collider) {
        m_colliders.push_back(collider);
    }

    void ColliderManager::removeCollider(Collider &collider) {
        auto it = std::find_if(m_colliders.begin(), m_colliders.end(), [&collider](const Collider &c) {
            return &c == &collider;
        });

        if (it != m_colliders.end()) {
            m_colliders.erase(it);
        }
    }

    void ColliderManager::clear() {
        m_colliders.clear();
    }

    std::vector<std::reference_wrapper<Collider>> &ColliderManager::getColliders() {
        return m_colliders;
    }

    void ColliderManager::physicsUpdate() {
        for (auto &collider : m_colliders) {
            collider.get().physicsUpdate();
        }
    }
}