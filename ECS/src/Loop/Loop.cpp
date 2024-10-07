#include <ECS/Loop.hpp>
#include <iostream>

namespace ECS {
    Loop::Loop(int fps)
        : m_isRunning(false),
        m_fps(fps),
        m_fixedTime(0.02f), // 50 Hz
        m_fpsTime(1.0f / fps),
        m_fixedDelta(0.0f),
        m_fpsDelta(0.0f),
        m_fpsLoss(0.0f)
    {
    }
    void Loop::run(Window& window)
    {
        m_isRunning = true;
        start(window); // start the event handler
        while (m_isRunning)
        {
            EventHandler::update();
            if (EventHandler::hasEvent(EventType::Closed))
            {
                stop();
                continue;
            }

            bool is_updated = false;
            bool is_fixed_updated = false;

            Time::updateForTick();
            m_fixedDelta += Time::getTickDeltaTime();
            m_fpsDelta += Time::getTickDeltaTime();

            if (m_fpsDelta >= m_fpsTime)
            {
                std::cout << "FPS: " << 1 / Time::getDeltaTime() << std::endl;
                Time::updateForFrame();
                m_fpsLoss = m_fpsDelta - m_fpsTime;
                m_fpsDelta = m_fpsLoss;
                is_updated = true;
            }

            if (m_fixedDelta >= m_fixedTime)
            {
                Time::updateForFixed();
                m_fixedDelta -= m_fixedTime;
                is_fixed_updated = true;
            }

            if (is_updated) {
                update();
            }
            if (is_fixed_updated) {
                fixedUpdate();
            }
            if (is_updated) {
                lateUpdate();
                window.clear();
                render();
                window.display();
            }
        }
    }

    void Loop::stop()
    {
        m_isRunning = false;
    }

    void Loop::start(Window& window)
    {
        //std::cout << "Loop started" << std::endl;
        EventHandler::init(window);
    }
    void Loop::update()
    {
        //std::cout << "Loop updated" << std::endl;
    }
    void Loop::fixedUpdate()
    {
        //std::cout << "Loop fixed updated" << std::endl;
    }
    void Loop::lateUpdate()
    {
        //std::cout << "Loop late updated" << std::endl;
    }
    void Loop::render()
    {
        //std::cout << "Loop rendered" << std::endl;
    }
}