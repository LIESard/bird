#include <map>
#include <fstream>
#include <iostream>
#include <exception>
#include <GL/glew.h>

#include "shader.hpp"

void Shader::setShader(std::string filename, GLenum shader_type) {
    if (m_shader_map.find(shader_type) != m_shader_map.end()) {
        if (glIsShader(m_shader_map[shader_type])) {
            glDeleteShader(m_shader_map[shader_type]);
        }
    }
    m_shader_map[shader_type] = glCreateShader(shader_type);

    std::ifstream source_file(filename);

    if (!source_file) {
        throw std::runtime_error({"Could not find file " + filename});
    }

    std::string source, line;
    while (std::getline(source_file, line)) {
        source += line + "\n";
    }

    const char *source_char = source.c_str();
    glShaderSource(m_shader_map[shader_type], 1, &source_char, NULL);
}

void Shader::compile() {
    for (auto &shader : m_shader_map) {
        glCompileShader(shader.second);
        glAttachShader(m_program, shader.second);

        // Check for errors
        GLint status;
        glGetShaderiv(shader.second, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            std::cout << "The shader could not be compiled" << std::endl;
            char error_log[512];
            glGetShaderInfoLog(shader.second, 512, NULL, error_log);
            std::cout << error_log << std::endl;
        }
    }

    glLinkProgram(m_program);
}

void Shader::use() {
    glBindFragDataLocation(m_program, 0, "colour");
    glUseProgram(m_program);
}

Shader::operator GLuint() const {
    return m_program;
}

Shader::Shader() {
    m_program = glCreateProgram();
}

Shader::~Shader() {
    for (auto &shader : m_shader_map) {
        glDeleteShader(shader.second);
    }
    glDeleteProgram(m_program);
}
