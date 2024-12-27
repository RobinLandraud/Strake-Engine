#pragma once
#include <ECS/EventHandler.hpp>
#include <ECS/Time.hpp>
#include <ECS/Camera.hpp>
#include <ECS/Scene.hpp>
#include <chrono>
#include <iostream>
#include <cmath>

namespace ECS {
    class GameLoop {
        public:
            explicit GameLoop(int fps = 60);
            ~GameLoop() = default;
            void run(Window& window, Scene &scene, bool debug = false);
            void stop();
        private:
            bool m_isRunning;
            const int m_fps;
            const float m_fixedTime;
            float m_fpsTime;
            float m_fixedDelta;
            float m_fpsDelta;
            void update(Scene &scene);
            void fixedUpdate(Scene &scene);
            void lateUpdate(Scene &scene);
            void render(Scene &scene, Window &window);
    };
}