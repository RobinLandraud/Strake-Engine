#include "Time.hpp"
#include "EventHandler.hpp" // already include Window.hpp
#include <chrono>

#pragma once

namespace ECS {
    class Loop {
        public:
            explicit Loop(int fps = 60);
            ~Loop() = default;
            void run(Window& window);
            void stop();
        private:
            bool m_isRunning;
            const int m_fps;
            const float m_fixedTime;
            float m_fpsTime;
            float m_fixedDelta;
            float m_fpsDelta;
            float m_fpsLoss;
            void start(Window& window);
            void update();
            void fixedUpdate();
            void lateUpdate();
            void render();
    };
}