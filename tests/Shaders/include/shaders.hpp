#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_content(const char* filename);


class Shader
{
    public:
        Shader(const std::string &vertexPath, const std::string &fragmentPath);
        void activate();
        void delete_shader();
        void getID();
    private:
        GLuint m_id;
        std::string m_fileExt[];
        static std::string read_file(const std::string& filename);
};