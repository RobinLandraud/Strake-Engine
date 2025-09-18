#include <Strake/Window/Window.hpp>
#include <Strake/Window/Key.hpp>
#include <Strake/Window/EventType.hpp>
#include <Strake/Window/Mouse.hpp>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>

#pragma once

namespace Strake {
    class EventHandler {
        public:
            static void init(Window &window);
            static void destroy();
            //prevent copying and moving
            EventHandler(const EventHandler&) = delete;
            EventHandler& operator=(const EventHandler&) = delete;
            EventHandler& operator=(EventHandler&&) = delete;
            EventHandler(EventHandler&&) = delete;
            ~EventHandler() = default;

            [[nodiscard]] static const std::vector<EventType>& getEvents();
            [[nodiscard]] static const std::vector<Key>& getKeysPressed();
            [[nodiscard]] static const std::vector<Key>& getKeysReleased();
            [[nodiscard]] static bool isKeyPressed(Key key);
            [[nodiscard]] static bool isKeyReleased(Key key);
            [[nodiscard]] static bool isKeyHeld(Key key);
            [[nodiscard]] static const mouse_t &getMouse();
            [[nodiscard]] static bool isMouseMoved(); // to do
            [[nodiscard]] static bool hasEvent(EventType event);

            static void update();
            static void setMouseCentered(bool centered);

        private:
            static EventHandler& getInstance();
            static inline std::unique_ptr<EventHandler> m_instance = nullptr;

            explicit EventHandler(Window &window);
            Window &m_window;

            std::vector<EventType> m_events;
            std::vector<Key> m_keysPressed;
            std::vector<Key> m_keysReleased;
            std::vector<Key> m_keyHeld;
            mouse_t m_mouse;
            bool m_mouseCentered = false;
            bool m_callbackSet = false;

            static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
            static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
            static void windowCloseCallback(GLFWwindow* window);
    };
}