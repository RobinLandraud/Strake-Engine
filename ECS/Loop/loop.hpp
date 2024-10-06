#include "../Time/time.hpp"
#include "../Window/window.hpp"
#include <chrono>

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
            void start();
            void update();
            void fixedUpdate();
            void lateUpdate();
            void render();
    };
}