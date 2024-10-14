#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <array>

class Shader
{
    public:
        Shader(const std::string &vertexPath, const std::string &fragmentPath);
        void activate();
        void delete_shader();
        GLuint getID();
    private:
        GLuint m_id;
        static const std::array<std::string, 2> m_fileExt;
        static std::string get_file_content(const std::string& filename);
};