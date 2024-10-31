#pragma once
#include <ECS/EventHandler.hpp>
#include <ECS/Time.hpp>
#include <chrono>
#include <iostream>

namespace ECS {
    class Loop {
        public:
            explicit Loop(int fps = 60);
            ~Loop() = default;
            void run(Window& window, bool debug = false);
            void stop();
        private:
            bool m_isRunning;
            const int m_fps;
            const float m_fixedTime;
            float m_fpsTime;
            float m_fixedDelta;
            float m_fpsDelta;
            void start(Window& window);
            void update();
            void fixedUpdate();
            void lateUpdate();
            void render();
    };
}