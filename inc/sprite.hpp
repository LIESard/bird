#ifndef SPRITE
#define SPRITE

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <array>

#include "entity.hpp"
#include "shader.hpp"

class Sprite {
public:
    enum Scene {
        BACKGROUND = 0,
        GAMEPLAY,
        FOREGROUND
    };
    std::array<GLfloat, 16> vertices;
    std::array<u_int8_t, 6> elements;
    GLuint vbo, ebo, vao, texture;
    GLint vao_index, tex_index;
    Scene scene;
    void sync(Entity &e);
    void updateTexture(Shader &s);

    Sprite(Entity &e, Shader &s, Scene sc);
    Sprite(Entity &e, Shader &s);
    Sprite(Shader &s, Scene sc);
    Sprite(Shader &s);
    ~Sprite();
};

#endif
