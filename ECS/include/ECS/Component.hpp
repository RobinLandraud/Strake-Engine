#pragma once
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <ECS/Entity.hpp>

namespace ECS {

    class Component;

    struct ComponentHolder {
        std::type_index type;
        std::unique_ptr<Component> component;

        ComponentHolder(std::type_index type, std::unique_ptr<Component> component)
            : type(type), component(std::move(component)) {}

        ComponentHolder(const ComponentHolder&) = delete;
        ComponentHolder& operator=(const ComponentHolder&) = delete;

        // Allow move semantics
        ComponentHolder(ComponentHolder&&) = default;
        ComponentHolder& operator=(ComponentHolder&&) = default;
    };

    class Component {
        public:
            explicit Component(
                const std::string &name,
                const std::string &parent,
                std::unordered_map<EntityTag, std::unordered_map<std::string, ComponentHolder>> &entities
            );
            virtual ~Component() = default;
            void awake();
            void start();
            void update();
            void fixedUpdate();
            void lateUpdate();
            void render();

        protected:
            const std::string m_name;
            std::unordered_map<EntityTag, std::unordered_map<std::string, ComponentHolder>> &r_entities;
            const std::string m_parent;
    };
}