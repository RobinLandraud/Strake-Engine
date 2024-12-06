#pragma once
#include <ECS/GameObject.hpp>
#include <memory>
#include <optional>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <glm/glm.hpp>

namespace ECS {

    class Camera;
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

            virtual void render(Camera &camera);

            [[nodiscard]] GameObject &getParent() const;
            [[nodiscard]] std::type_index getDerivedType() const;

        protected:
            void setDerivedType(const std::type_index &type);

        private:
            GameObject &r_parent;
            std::type_index m_derivedType = typeid(Component);
    };
}