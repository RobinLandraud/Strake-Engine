#pragma once
#include <string>
#include <unordered_map>
#include <typeindex>
#include <memory>

namespace ECS {

    class Component;

    struct ComponentHolder {
        std::type_index type;
        std::unique_ptr<Component> component;

        ComponentHolder(std::type_index type, std::unique_ptr<Component> component)
            : type(type), component(std::move(component)) {}
    };

    class Component {
        public:
            explicit Component(const std::string &name, std::unordered_map<std::string, ComponentHolder> &parentComponents);
            virtual ~Component() = default;
            void awake();
            void start();
            void update();
            void fixedUpdate();
            void lateUpdate();
            void render();

        protected:
            const uint32_t m_id;
            const std::string m_name;

        private:
            static uint32_t m_idCounter;
            std::unordered_map<std::string, ComponentHolder> &m_parentComponents;
    };
}