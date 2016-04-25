#include <chrono>
#include <vector>
#include <iostream>
#include "sprite.hpp"
#include "shader.hpp"
#include "bird.hpp"
#include "block.hpp"
#include <GLFW/glfw3.h>

constexpr int WIDTH = 640, HEIGHT = 480;
constexpr float FRAME_TIME = 1.f / 60.f;

float timeSince(std::chrono::high_resolution_clock::time_point time_start) {    
        auto time_now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::duration<float>>
               (time_now - time_start).count() / 2;
}

void showPosition(Entity &e) {
    std::cout << e.acceleration.x << ", " << e.acceleration.y << "  "
              << e.velocity.x << ", " << e.velocity.y << "  "
              << e.position.x << ", " << e.position.y << std::endl;
}

void showPosition(Sprite &s) {
    for (unsigned int i = 0; i < s.elements.size(); ++i) {
        std::cout << s.vertices[s.elements[i]] << ", ";
    }

    std::cout << std::endl;
}

void showVertices(Entity &e) {
    for (float f : e.vertices) {
        std::cout << f << std::endl;
    }
}

void showVertices(Sprite &s) {
    for (float f : s.vertices) {
        std::cout << f << std::endl;
    }
}

void draw(GLFWwindow *window, std::vector<Sprite*> &sprites) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (unsigned int i = 0; i < sprites.size(); i++) {
        glBindVertexArray(sprites[i]->vao);
        glBindBuffer(GL_ARRAY_BUFFER, sprites[i]->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprites[i]->ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    }

    glfwSwapBuffers(window);
}

void update(GLFWwindow *window, std::vector<Sprite*> &sprites) {}

GLFWwindow *createWindow() {
    GLFWwindow *window = NULL;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Bird", NULL, NULL);
    glfwMakeContextCurrent(window);

    return window;
}

int main() {
    glfwInit();
    GLFWwindow *window = createWindow();
    glewExperimental = GL_TRUE;
    glewInit();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    Shader shader;
    shader.setShader("res/shaders/shader.vert", GL_VERTEX_SHADER);
    shader.setShader("res/shaders/shader.frag", GL_FRAGMENT_SHADER);
    shader.compile();
    shader.use();

    //              position,       size
    Bird player(    {-640, -480},   {64, 64});
    Block block(    {0, -480},      {64, 64});
    Sprite player_sprite(player, shader);
    Sprite block_sprite(block, shader);

    std::vector<Entity*> entities = {&player, &block};

    // Create list of drawable entities
    std::vector<Sprite*> sprites = {&player_sprite, &block_sprite};

    puts("Birds are Ok, I guess");

    double delta_time = 0;
    glClearColor(0.f, 0.5f, 1.f, 1.f);

    while (!glfwWindowShouldClose(window)) {
        delta_time += glfwGetTime();
        glfwSetTime(0);

        while (delta_time > FRAME_TIME) {
            delta_time -= FRAME_TIME;

            glfwPollEvents();
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GL_TRUE);
            }
            player.move(window);

            for (Entity *e : entities) {
                e->update(FRAME_TIME);
            }
            player.handleCollision(block, FRAME_TIME);
            player_sprite.sync(player);
            block_sprite.sync(block);
        }

        draw(window, sprites);
    }

    glfwTerminate();

    return 0;
}
