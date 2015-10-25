#ifndef SHADER
#define SHADER

#include <map>
#include <string>
#include <GL/gl.h>

class Shader {
private:
    std::map<GLenum, GLuint> m_shader_map;
    GLuint m_program;

public:
    void setShader(std::string filename, GLuint shader);
    void compile();
    void use();

    operator GLuint() const;

    Shader();
    ~Shader();
};

#endif
