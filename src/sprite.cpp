#include "sprite.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG   
#include "stb_image.h"
#include <iostream>

constexpr std::array<float, 16> genVertices(Entity &e) {
    return {{
        e.position.x, e.position.y,                         0.f, 16.f,
        e.position.x + e.size.x, e.position.y,              16.f, 16.f,
        e.position.x + e.size.x, e.position.y + e.size.y,   16.f, 0.f,
        e.position.x, e.position.y + e.size.y,              0.f, 0.f
    }};
}

void Sprite::sync(Entity e) {
    vertices = genVertices(e);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);
}

Sprite::Sprite(Shader &s) {
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vao_index = glGetAttribLocation(s, "position");
    glVertexAttribPointer(vao_index, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vao_index);
}

Sprite::Sprite(Entity &e, Shader &s) {
    vertices = genVertices(e);

    elements = {{
        0, 1, 2,
        2, 3, 0
    }};

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size(),
                 elements.data(), GL_STATIC_DRAW);

    vao_index = glGetAttribLocation(s, "position");
    glVertexAttribPointer(vao_index, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(vao_index);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    int width, height, img_comp;
    unsigned char *image = stbi_load("res/spritesheet.png", &width, &height,
                                     &img_comp, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image);
    tex_index = glGetAttribLocation(s, "tex_coord");
    glEnableVertexAttribArray(tex_index);
    glVertexAttribPointer(tex_index, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void*)(2 * sizeof(float)));


    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST);
}

Sprite::~Sprite() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}
