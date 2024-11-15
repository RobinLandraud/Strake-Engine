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
                GameObject &parent
            );
            virtual ~Component() = default;
            virtual void awake();
            virtual void start();
            virtual void update();
            virtual void fixedUpdate();
            virtual void lateUpdate();

            virtual void render(); // not accessible from certain inherited classes like Camera, Script, etc.

            [[nodiscard]] GameObject &getParent() const;

        private:
            GameObject &r_parent;
    };
}