#pragma once
#include <ECS/GameObject.hpp>
#include <memory>
#include <optional>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace ECS {
    class Component {
        public:
            explicit Component(
                const GameObject &parent
            );
            virtual ~Component() = default;
            virtual void awake();
            virtual void start();
            virtual void update();
            virtual void fixedUpdate();
            virtual void lateUpdate();
            virtual void render();

            [[nodiscard]] const GameObject &getParent() const;

        private:
            const GameObject &r_parent;
    };
}