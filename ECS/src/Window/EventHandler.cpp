#include <ECS/EventHandler.hpp>
#include <iostream>

namespace ECS
{
    EventHandler::EventHandler(Window& window) :
        m_mouse({0, 0, false, false, false, 0}),
        m_window(window)
    {
        glfwSetWindowUserPointer(m_window.getGLFWWindow(), this);
        glfwSetKeyCallback(m_window.getGLFWWindow(), keyCallback);
        glfwSetMouseButtonCallback(m_window.getGLFWWindow(), mouseButtonCallback);
        glfwSetCursorPosCallback(m_window.getGLFWWindow(), cursorPosCallback);
        glfwSetScrollCallback(m_window.getGLFWWindow(), scrollCallback);
        glfwSetWindowCloseCallback(m_window.getGLFWWindow(), windowCloseCallback);
    }

    void EventHandler::init(Window &window)
    {
        if (m_instance == nullptr)
        {
            // new because constructor is private (canno't use make_unique)
            m_instance = std::unique_ptr<EventHandler>(new EventHandler(window));
        }
    }

    void EventHandler::destroy()
    {
        m_instance.reset();
    }

    EventHandler& EventHandler::getInstance()
    {
        if (m_instance == nullptr)
        {
            throw std::runtime_error("EventHandler not initialized. Call init() first.");
        }
        return *m_instance;
    }

    void EventHandler::update()
    {
        EventHandler &eventHandler = getInstance();
        eventHandler.m_events.clear();
        eventHandler.m_keysPressed.clear();
        eventHandler.m_keysReleased.clear();
        eventHandler.m_mouse.wheel = 0;
        glfwPollEvents();
    }

    void EventHandler::setMouseCentered(bool centered)
    {
        EventHandler &eventHandler = getInstance();
        eventHandler.m_mouseCentered = centered;
    }

    bool EventHandler::hasEvent(EventType event)
    {
        EventHandler &eventHandler = getInstance();
        return std::find(eventHandler.m_events.begin(), eventHandler.m_events.end(), event) != eventHandler.m_events.end();
    }

    bool EventHandler::isKeyPressed(Key key)
    {
        EventHandler &eventHandler = getInstance();
        return std::find(eventHandler.m_keysPressed.begin(), eventHandler.m_keysPressed.end(), key) != eventHandler.m_keysPressed.end();
    }

    bool EventHandler::isKeyReleased(Key key)
    {
        EventHandler &eventHandler = getInstance();
        return std::find(eventHandler.m_keysReleased.begin(), eventHandler.m_keysReleased.end(), key) != eventHandler.m_keysReleased.end();
    }

    bool EventHandler::isKeyHeld(Key key)
    {
        EventHandler &eventHandler = getInstance();
        return std::find(eventHandler.m_keyHeld.begin(), eventHandler.m_keyHeld.end(), key) != eventHandler.m_keyHeld.end();
    }

    mouse_t const& EventHandler::getMouse()
    {
        EventHandler &eventHandler = getInstance();
        return eventHandler.m_mouse;
    }

    void EventHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        EventHandler &handler = *static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
            handler.m_keysPressed.push_back(static_cast<Key>(key));
            handler.m_keyHeld.push_back(static_cast<Key>(key));
            handler.m_events.push_back(EventType::KeyPressed);
        }
        else if (action == GLFW_RELEASE)
        {
            handler.m_keysReleased.push_back(static_cast<Key>(key));
            handler.m_keyHeld.erase(std::remove(handler.m_keyHeld.begin(), handler.m_keyHeld.end(), static_cast<Key>(key)), handler.m_keyHeld.end());
            handler.m_events.push_back(EventType::KeyReleased);
        }
    }

    void EventHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        EventHandler &handler = *static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
        if (action == GLFW_PRESS)
        {
            handler.m_events.push_back(EventType::MouseButtonPressed);
            switch (button)
            {
                case GLFW_MOUSE_BUTTON_LEFT:
                    handler.m_mouse.left = true;
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                    handler.m_mouse.right = true;
                    break;
                case GLFW_MOUSE_BUTTON_MIDDLE:
                    handler.m_mouse.middle = true;
                    break;
                default:
                    break;
            }
        } else if (action == GLFW_RELEASE)
        {
            handler.m_events.push_back(EventType::MouseButtonReleased);
            switch (button)
            {
                case GLFW_MOUSE_BUTTON_LEFT:
                    handler.m_mouse.left = false;
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                    handler.m_mouse.right = false;
                    break;
                case GLFW_MOUSE_BUTTON_MIDDLE:
                    handler.m_mouse.middle = false;
                    break;
                default:
                    break;
            }
        }
    }

    void EventHandler::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
    {
        EventHandler &handler = *static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
        if (handler.m_callbackSet == true)
        {
            handler.m_callbackSet = false;
            return;
        }
        handler.m_events.push_back(EventType::MouseMoved);
        handler.m_mouse.x = static_cast<float>(xpos) - handler.m_window.getWidth() / 2;
        handler.m_mouse.y = static_cast<float>(ypos) - handler.m_window.getHeight() / 2;
        if (handler.m_mouseCentered)
        {
            glfwSetCursorPos(window, handler.m_window.getWidth() / 2, handler.m_window.getHeight() / 2);
            handler.m_callbackSet = true;
        }
    }

    void EventHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        EventHandler &handler = *static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
        handler.m_events.push_back(EventType::MouseWheelScrolled);
        handler.m_mouse.wheel = static_cast<float>(yoffset);
    }

    void EventHandler::windowCloseCallback(GLFWwindow* window)
    {
        EventHandler &handler = *static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
        handler.m_events.push_back(EventType::Closed);
    }
}