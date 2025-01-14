#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <GL/glew.h>

namespace Strake {
    class Shader {
        public:
            Shader(const std::string &path, GLenum type);
            ~Shader();
            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;
            Shader& operator=(Shader&&) = delete;
            Shader(Shader&&) = delete;

            [[nodiscard]] GLuint getID() const;
        private:
            GLuint m_shader;
    };
}