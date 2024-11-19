#include <ECS/Loop.hpp>

namespace ECS {
    Loop::Loop(int fps)
        : m_isRunning(false),
        m_fps(fps),
        m_fixedTime(0.02f), // 50 Hz
        m_fpsTime(1.0f / static_cast<float>(m_fps)),
        m_fixedDelta(0.0f),
        m_fpsDelta(0.0f)
    {
    }
    void Loop::run(Window& window, Scene &scene, bool debug)
    {
        m_isRunning = true;

        float actual_fps = 0.0f; // only for debug
        float loss = 0.0f; // only for debug
        float sum = 0.0f; // only for debug
        float f_m_fps = static_cast<float>(m_fps); // only for debug

        float current_delta = 0.0f;
        std::vector<float> fps_buffer;
        bool is_updated = false;
        bool is_fixed_updated = false;

        while (m_isRunning)
        {
            EventHandler::update();
            if (EventHandler::hasEvent(EventType::Closed))
            {
                stop();
                continue;
            }

            is_updated = false;
            is_fixed_updated = false;

            Time::updateForTick();
            current_delta = Time::getTickDeltaTime(); // for update, render
            m_fixedDelta += current_delta;
            m_fpsDelta += current_delta;

            if (m_fpsDelta >= m_fpsTime)
            {
                if (debug) {
                    fps_buffer.push_back(1.0f / m_fpsDelta);
                    if (fps_buffer.size() >= 500) {
                        sum = 0.0f;
                        for (auto &fps : fps_buffer) {
                            sum += fps;
                        }
                        actual_fps = sum / 500.0f;
                        loss = (f_m_fps - actual_fps) * 100.0f / f_m_fps;
                        std::cout << "FPS: " << std::floor(actual_fps) << " LOSS: " << std::floor(loss * 100.0f) / 100.0f << "%" << std::endl;
                        fps_buffer.clear();
                    }
                }
                Time::updateForFrame();
                m_fpsDelta = std::fmod(m_fpsDelta, m_fpsTime);
                is_updated = true;
            }

            if (m_fixedDelta >= m_fixedTime)
            {
                Time::updateForFixed();
                m_fixedDelta = m_fixedDelta - m_fixedTime;
                is_fixed_updated = true;
            }

            if (is_updated) {
                update(scene);
            }
            if (is_fixed_updated) {
                fixedUpdate(scene);
            }
            if (is_updated) {
                lateUpdate(scene);
                ECS::Window::clear();
                render(scene);
                window.display();
            }
        }
    }

    void Loop::stop()
    {
        m_isRunning = false;
        glfwTerminate();
    }

    void Loop::update(Scene &scene)
    {
        scene.update();
    }
    void Loop::fixedUpdate(Scene &scene)
    {
        scene.fixedUpdate();
    }
    void Loop::lateUpdate(Scene &scene)
    {
        scene.lateUpdate();
    }
    void Loop::render(Scene &scene)
    {
        scene.render();
    }
}