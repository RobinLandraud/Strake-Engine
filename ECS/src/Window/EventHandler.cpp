#include <ECS/EventHandler.hpp>
// include sfml events
#include <SFML/Window/Event.hpp>

namespace ECS
{
    std::unique_ptr<EventHandler> EventHandler::m_instance = nullptr;

    EventHandler::EventHandler(Window& window)
        : m_events(std::vector<EventType>()),
        m_keysPressed(std::vector<Key>()),
        m_keysReleased(std::vector<Key>()),
        m_keyHeld(std::vector<Key>()),
        m_mouse({0, 0, false, false, false, 0}),
        m_window(window)
    {
    }

    EventHandler::~EventHandler()
    {
        // no need to delete the instance, unique_ptr will handle it
    }

    EventHandler& EventHandler::getInstance()
    {
        if (m_instance == nullptr)
        {
            throw std::runtime_error("EventHandler not initialized. Call init() first.");
        }
        return *m_instance;
    }

    void EventHandler::init(Window &window)
    {
        if (m_instance == nullptr)
        {
            m_instance = std::unique_ptr<EventHandler>(new EventHandler(window));
        }
    }

    void EventHandler::update()
    {
        EventHandler &eventHandler = getInstance();
        sf::Event event;
        //reset the events
        eventHandler.m_events.clear();
        eventHandler.m_keysPressed.clear();
        eventHandler.m_keysReleased.clear();
        eventHandler.m_mouse.wheel = 0;

        while (eventHandler.m_window.getRenderWindow().pollEvent(event))
        {
            if (eventHandler.m_eventTypes.find(event.type) != eventHandler.m_eventTypes.end()) {
                eventHandler.m_events.push_back(eventHandler.m_eventTypes.at(event.type));
                if (event.type == sf::Event::MouseMoved) //update mouse position
                {
                    eventHandler.m_mouse.x = event.mouseMove.x;
                    eventHandler.m_mouse.y = event.mouseMove.y;
                }
                else if (event.type == sf::Event::MouseButtonPressed) //update mouse button
                {
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            eventHandler.m_mouse.left = true;
                            break;
                        case sf::Mouse::Right:
                            eventHandler.m_mouse.right = true;
                            break;
                        case sf::Mouse::Middle:
                            eventHandler.m_mouse.middle = true;
                            break;
                        default:
                            break;
                    }
                }
                else if (event.type == sf::Event::MouseButtonReleased) //update mouse button
                {
                    switch (event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            eventHandler.m_mouse.left = false;
                            break;
                        case sf::Mouse::Right:
                            eventHandler.m_mouse.right = false;
                            break;
                        case sf::Mouse::Middle:
                            eventHandler.m_mouse.middle = false;
                            break;
                        default:
                            break;
                    }
                }
                else if (event.type == sf::Event::MouseWheelScrolled) //update mouse scroll
                {
                    eventHandler.m_mouse.wheel = event.mouseWheelScroll.delta;
                }
                else if (event.type == sf::Event::KeyPressed) // update key pressed
                {
                    if (eventHandler.m_keys.find(event.key.code) != eventHandler.m_keys.end())
                    {
                        eventHandler.m_keysPressed.push_back(eventHandler.m_keys.at(event.key.code));
                        eventHandler.m_keyHeld.push_back(eventHandler.m_keys.at(event.key.code));
                    }
                }
                else if (event.type == sf::Event::KeyReleased) // update key released
                {
                    if (eventHandler.m_keys.find(event.key.code) != eventHandler.m_keys.end())
                    {
                        eventHandler.m_keysReleased.push_back(eventHandler.m_keys.at(event.key.code));
                        auto it = std::find(eventHandler.m_keyHeld.begin(), eventHandler.m_keyHeld.end(), eventHandler.m_keys.at(event.key.code));
                        if (it != eventHandler.m_keyHeld.end())
                        {
                            eventHandler.m_keyHeld.erase(it);
                        }
                    }
                }
            }
        }
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
}