#include "time.hpp"

namespace ECS {
    std::unique_ptr<Time> Time::m_instance = nullptr;

    Time::Time()
    {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        m_time = now;
        m_lastTime = now;
        m_tickTime = now;
        m_tickLastTime = now;
        m_fixedTime = now;
        m_fixedLastTime = now;
    }

    Time::~Time()
    {
        m_instance.reset(); //reset the pointer to nullptr
    }

    Time& Time::getInstance()
    {
        if (!m_instance)
        {
            m_instance.reset(new Time());
        }
        return *m_instance; //dereference the pointer to get the object
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