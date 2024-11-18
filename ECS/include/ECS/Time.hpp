#pragma once
#include <chrono>
#include <memory>

namespace ECS {
    class Time {
        public:
            // no nead of constructor and avoid using getInstance() method
            static void updateForTick();
            static void updateForFrame();
            static void updateForFixed();
            [[nodiscard]] static float getDeltaTime();
            [[nodiscard]] static float getFixedDeltaTime();
            [[nodiscard]] static float getTickDeltaTime();

            //prevent copying and moving
            Time(const Time&) = delete;
            Time& operator=(const Time&) = delete;
            Time& operator=(Time&&) = delete;
            Time(Time&&) = delete;

            ~Time() = default;

        private:
            static Time& getInstance();
            static std::unique_ptr<Time> m_instance;

            std::chrono::high_resolution_clock::time_point m_time;
            std::chrono::duration<float> m_deltaTime;
            std::chrono::high_resolution_clock::time_point m_lastTime;
            std::chrono::high_resolution_clock::time_point m_tickTime;
            std::chrono::duration<float> m_tickDeltaTime;
            std::chrono::high_resolution_clock::time_point m_tickLastTime;
            std::chrono::high_resolution_clock::time_point m_fixedTime;
            std::chrono::duration<float> m_fixedDeltaTime;
            std::chrono::high_resolution_clock::time_point m_fixedLastTime;


            [[nodiscard]] float getDeltaTimeInternal() const;
            [[nodiscard]] float getFixedDeltaTimeInternal() const;
            [[nodiscard]] float getTickDeltaTimeInternal() const;

            //private constructor to prevent instantiation
            Time();
    };
}