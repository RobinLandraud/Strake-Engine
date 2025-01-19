#pragma once

#include <Strake/Component/Collider/Collider.hpp>
#include <Strake/Component/Collider/SphereCollider.hpp>

namespace Strake {
    class ColliderManager {
        public:
            explicit ColliderManager(EventDispatcher &eventDispatcher);
            ~ColliderManager();
            ColliderManager(const ColliderManager &other) = delete;
            ColliderManager(ColliderManager &&other) = delete;
            ColliderManager &operator=(const ColliderManager &other) = delete;
            ColliderManager &operator=(ColliderManager &&other) = delete;

            void addCollider(Collider &Collider);
            void removeCollider(Collider &Collider);
            void clear();
            [[nodiscard]] std::vector<std::reference_wrapper<Collider>> &getColliders();

        private:
            std::vector<std::reference_wrapper<Collider>> m_colliders;

            EventDispatcher &m_eventDispatcher;
            std::unordered_map<EventDispatcher::EventID, std::string> m_subscriptions;
    };
}