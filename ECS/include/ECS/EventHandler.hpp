#include <vector>
#include <ECS/Window.hpp>
#include <memory>

#pragma once

namespace ECS {
    enum Key {
        Unknown = -1,
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Escape,
        LControl,
        LShift,
        LAlt,
        LSystem,
        RControl,
        RShift,
        RAlt,
        RSystem,
        Menu,
        LBracket,
        RBracket,
        SemiColon,
        Comma,
        Period,
        Quote,
        Slash,
        BackSlash,
        Tilde,
        Equal,
        Dash,
        Hyphen,
        Space,
        Return,
        Enter,
        BackSpace,
        Tab,
        PageUp,
        PageDown,
        End,
        Home,
        Insert,
        Delete,
        Add,
        Subtract,
        Multiply,
        Divide,
        Left,
        Right,
        Up,
        Down,
        Numpad0,
        Numpad1,
        Numpad2,
        Numpad3,
        Numpad4,
        Numpad5,
        Numpad6,
        Numpad7,
        Numpad8,
        Numpad9,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        Pause
    };

    enum EventType {
        Other = -1,
        Closed = 0,
        Resized,
        LostFocus,
        GainedFocus,
        TextEntered,
        KeyPressed,
        KeyReleased,
        MouseMoved,
        MouseButtonPressed,
        MouseEntered,
        MouseButtonReleased,
        MouseWheelMoved,
        MouseWheelScrolled,
        MouseLeft,
        JoystickButtonPressed,
        JoystickButtonReleased,
        JoystickMoved,
        JoystickConnected,
        JoystickDisconnected,
        TouchBegan,
        TouchMoved,
        TouchEnded,
        SensorChanged,
        Count
    };

    struct mouse_t {
        float x;     /*!< X position */
        float y;     /*!< Y position */
        bool left;   /*!< Left button */
        bool right;  /*!< Right button */
        bool middle; /*!< Middle button */
        float wheel; /*!< Wheel */
    };

    class EventHandler {
        public:
            static void init(Window &window);
            static void update();
            [[nodiscard]] static const std::vector<EventType>& getEvents();
            [[nodiscard]] static const std::vector<Key>& getKeysPressed();
            [[nodiscard]] static const std::vector<Key>& getKeysReleased();
            [[nodiscard]] static bool isKeyPressed(Key key);
            [[nodiscard]] static bool isKeyReleased(Key key);
            [[nodiscard]] static bool isKeyHeld(Key key);
            [[nodiscard]] static const mouse_t &getMouse();
            [[nodiscard]] static bool isMouseMoved(); // to do
            [[nodiscard]] static bool hasEvent(EventType event);

            //prevent copying and moving
            EventHandler(const EventHandler&) = delete;
            EventHandler& operator=(const EventHandler&) = delete;
            EventHandler& operator=(EventHandler&&) = delete;
            EventHandler(EventHandler&&) = delete;

            ~EventHandler();

        private:
            static EventHandler& getInstance();
            static std::unique_ptr<EventHandler> m_instance;

            EventHandler(Window &window);
            Window &m_window;

            std::vector<EventType> m_events;
            std::vector<Key> m_keysPressed;
            std::vector<Key> m_keysReleased;
            std::vector<Key> m_keyHeld;
            mouse_t m_mouse;

            const std::unordered_map<sf::Keyboard::Key, Key> m_keys = {
                {sf::Keyboard::Unknown, Unknown},
                {sf::Keyboard::A, Key::A},
                {sf::Keyboard::B, Key::B},
                {sf::Keyboard::C, Key::C},
                {sf::Keyboard::D, Key::D},
                {sf::Keyboard::E, Key::E},
                {sf::Keyboard::F, Key::F},
                {sf::Keyboard::G, Key::G},
                {sf::Keyboard::H, Key::H},
                {sf::Keyboard::I, Key::I},
                {sf::Keyboard::J, Key::J},
                {sf::Keyboard::K, Key::K},
                {sf::Keyboard::L, Key::L},
                {sf::Keyboard::M, Key::M},
                {sf::Keyboard::N, Key::N},
                {sf::Keyboard::O, Key::O},
                {sf::Keyboard::P, Key::P},
                {sf::Keyboard::Q, Key::Q},
                {sf::Keyboard::R, Key::R},
                {sf::Keyboard::S, Key::S},
                {sf::Keyboard::T, Key::T},
                {sf::Keyboard::U, Key::U},
                {sf::Keyboard::V, Key::V},
                {sf::Keyboard::W, Key::W},
                {sf::Keyboard::X, Key::X},
                {sf::Keyboard::Y, Key::Y},
                {sf::Keyboard::Z, Key::Z},
                {sf::Keyboard::Num0, Key::Num0},
                {sf::Keyboard::Num1, Key::Num1},
                {sf::Keyboard::Num2, Key::Num2},
                {sf::Keyboard::Num3, Key::Num3},
                {sf::Keyboard::Num4, Key::Num4},
                {sf::Keyboard::Num5, Key::Num5},
                {sf::Keyboard::Num6, Key::Num6},
                {sf::Keyboard::Num7, Key::Num7},
                {sf::Keyboard::Num8, Key::Num8},
                {sf::Keyboard::Num9, Key::Num9},
                {sf::Keyboard::Escape, Key::Escape},
                {sf::Keyboard::LControl, Key::LControl},
                {sf::Keyboard::LShift, Key::LShift},
                {sf::Keyboard::LAlt, Key::LAlt},
                {sf::Keyboard::LSystem, Key::LSystem},
                {sf::Keyboard::RControl, Key::RControl},
                {sf::Keyboard::RShift, Key::RShift},
                {sf::Keyboard::RAlt, Key::RAlt},
                {sf::Keyboard::RSystem, Key::RSystem},
                {sf::Keyboard::Menu, Key::Menu},
                {sf::Keyboard::LBracket, Key::LBracket},
                {sf::Keyboard::RBracket, Key::RBracket},
                {sf::Keyboard::SemiColon, Key::SemiColon},
                {sf::Keyboard::Comma, Key::Comma},
                {sf::Keyboard::Period, Key::Period},
                {sf::Keyboard::Quote, Key::Quote},
                {sf::Keyboard::Slash, Key::Slash},
                {sf::Keyboard::BackSlash, Key::BackSlash},
                {sf::Keyboard::Tilde, Key::Tilde},
                {sf::Keyboard::Equal, Key::Equal},
                {sf::Keyboard::Dash, Key::Dash},
                {sf::Keyboard::Space, Key::Space},
                {sf::Keyboard::Return, Key::Return},
                {sf::Keyboard::BackSpace, Key::BackSpace},
                {sf::Keyboard::Tab, Key::Tab},
                {sf::Keyboard::PageUp, Key::PageUp},
                {sf::Keyboard::PageDown, Key::PageDown},
                {sf::Keyboard::End, Key::End},
                {sf::Keyboard::Home, Key::Home},
                {sf::Keyboard::Insert, Key::Insert},
                {sf::Keyboard::Delete, Key::Delete},
                {sf::Keyboard::Add, Key::Add},
                {sf::Keyboard::Subtract, Key::Subtract},
                {sf::Keyboard::Multiply, Key::Multiply},
                {sf::Keyboard::Divide, Key::Divide},
                {sf::Keyboard::Left, Key::Left},
                {sf::Keyboard::Right, Key::Right},
                {sf::Keyboard::Up, Key::Up},
                {sf::Keyboard::Down, Key::Down},
                {sf::Keyboard::Numpad0, Key::Numpad0},
                {sf::Keyboard::Numpad1, Key::Numpad1},
                {sf::Keyboard::Numpad2, Key::Numpad2},
                {sf::Keyboard::Numpad3, Key::Numpad3},
                {sf::Keyboard::Numpad4, Key::Numpad4},
                {sf::Keyboard::Numpad5, Key::Numpad5},
                {sf::Keyboard::Numpad6, Key::Numpad6},
                {sf::Keyboard::Numpad7, Key::Numpad7},
                {sf::Keyboard::Numpad8, Key::Numpad8},
                {sf::Keyboard::Numpad9, Key::Numpad9},
                {sf::Keyboard::F1, Key::F1},
                {sf::Keyboard::F2, Key::F2},
                {sf::Keyboard::F3, Key::F3},
                {sf::Keyboard::F4, Key::F4},
                {sf::Keyboard::F5, Key::F5},
                {sf::Keyboard::F6, Key::F6},
                {sf::Keyboard::F7, Key::F7},
                {sf::Keyboard::F8, Key::F8},
                {sf::Keyboard::F9, Key::F9},
                {sf::Keyboard::F10, Key::F10},
                {sf::Keyboard::F11, Key::F11},
                {sf::Keyboard::F12, Key::F12},
                {sf::Keyboard::F13, Key::F13},
                {sf::Keyboard::F14, Key::F14},
                {sf::Keyboard::F15, Key::F15},
                {sf::Keyboard::Pause, Key::Pause}
            };  /*!< The keys */

            const std::unordered_map<sf::Event::EventType, EventType> m_eventTypes = {
                {sf::Event::Closed, Closed},
                {sf::Event::Resized, Resized},
                {sf::Event::LostFocus, LostFocus},
                {sf::Event::GainedFocus, GainedFocus},
                {sf::Event::TextEntered, TextEntered},
                {sf::Event::KeyPressed, KeyPressed},
                {sf::Event::KeyReleased, KeyReleased},
                {sf::Event::MouseWheelMoved, MouseWheelMoved},
                {sf::Event::MouseWheelScrolled, MouseWheelScrolled},
                {sf::Event::MouseButtonPressed, MouseButtonPressed},
                {sf::Event::MouseButtonReleased, MouseButtonReleased},
                {sf::Event::MouseMoved, MouseMoved},
                {sf::Event::MouseEntered, MouseEntered},
                {sf::Event::MouseLeft, MouseLeft},
                {sf::Event::JoystickButtonPressed, JoystickButtonPressed},
                {sf::Event::JoystickButtonReleased, JoystickButtonReleased},
                {sf::Event::JoystickMoved, JoystickMoved},
                {sf::Event::JoystickConnected, JoystickConnected},
                {sf::Event::JoystickDisconnected, JoystickDisconnected},
                {sf::Event::TouchBegan, TouchBegan},
                {sf::Event::TouchMoved, TouchMoved},
                {sf::Event::TouchEnded, TouchEnded},
                {sf::Event::SensorChanged, SensorChanged},
                {sf::Event::Count, Count}};
            };
}