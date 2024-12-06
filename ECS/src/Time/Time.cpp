#include <ECS/Time.hpp>

namespace ECS {
    Time::Time() : 
        m_time(std::chrono::high_resolution_clock::now()),
        m_lastTime(std::chrono::high_resolution_clock::now()),
        m_tickTime(std::chrono::high_resolution_clock::now()),
        m_tickLastTime(std::chrono::high_resolution_clock::now()),
        m_fixedTime(std::chrono::high_resolution_clock::now()),
        m_fixedLastTime(std::chrono::high_resolution_clock::now()),
        m_deltaTime(std::chrono::duration<float>(0.0f)),
        m_tickDeltaTime(std::chrono::duration<float>(0.0f)),
        m_fixedDeltaTime(std::chrono::duration<float>(0.0f))
    {
    }

    void Time::init()
    {
        if (m_instance == nullptr)
        {
            m_instance = std::unique_ptr<Time>(new Time());
        }
    }

    void Time::destroy()
    {
        m_instance.reset();
    }

    Time& Time::getInstance()
    {
        if (m_instance == nullptr)
        {
            throw std::runtime_error("Time not initialized. Call init() first.");
        }
        return *m_instance;
    }

    void Time::updateForTick()
    {
        Time& time = getInstance();
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        time.m_tickDeltaTime = std::chrono::duration<float>(now - time.m_tickLastTime);
        time.m_tickTime += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(time.m_tickDeltaTime);
        time.m_tickLastTime = now;
    }

    void Time::updateForFrame()
    {
        Time& time = getInstance();
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        time.m_deltaTime = std::chrono::duration<float>(now - time.m_lastTime);
        time.m_time += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(time.m_deltaTime);
        time.m_lastTime = now;
    }

    void Time::updateForFixed()
    {
        Time& time = getInstance();
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        time.m_fixedDeltaTime = std::chrono::duration<float>(now - time.m_fixedLastTime);
        time.m_fixedTime += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(time.m_fixedDeltaTime);
        time.m_fixedLastTime = now;
    }

    float Time::getDeltaTimeInternal() const
    {
        return m_deltaTime.count();
    }

    float Time::getFixedDeltaTimeInternal() const
    {
        return m_fixedDeltaTime.count();
    }

    float Time::getTickDeltaTimeInternal() const
    {
        return m_tickDeltaTime.count();
    }

    float Time::getDeltaTime()
    {
        return getInstance().getDeltaTimeInternal();
    }

    float Time::getFixedDeltaTime()
    {
        return getInstance().getFixedDeltaTimeInternal();
    }

    float Time::getTickDeltaTime()
    {
        return getInstance().getTickDeltaTimeInternal();
    }
}