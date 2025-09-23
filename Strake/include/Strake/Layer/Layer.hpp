#pragma once

#include <string>

namespace Strake {
    class Layer {
        public:
            Layer();
            Layer(const std::string &name, int priority);
            ~Layer() = default;
            Layer(const Layer &layer) = delete;
            Layer &operator=(const Layer &layer) = delete;
            Layer(Layer &&layer) = delete;
            Layer &operator=(Layer &&layer) = delete;

            [[nodiscard]] std::string getName() const;
            [[nodiscard]] int getPriority() const;
            [[nodiscard]] int getBitMask() const;

            void setName(const std::string &&name);
            void setPriority(int priority);

        private:
            std::string m_name;
            int m_priority;
            int m_bitMask; // used by masks (1 << id)
    };
}