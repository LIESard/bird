#include <iostream>
#include <chrono>
#include <vector>
#include "entitymanager.hpp"
#include "spritemanager.hpp"
#include "sprite.hpp"
#include "shader.hpp"
#include "block.hpp"
#include "cloud.hpp"
#include "bird.hpp"
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

    //          position
    Bird player({-640, -480});
    Block block({0, -480});
    Cloud cloud({-120, -120});
    Sprite player_sprite(player, shader);
    Sprite block_sprite(block, shader);
    Sprite cloud_sprite(cloud, shader);

    EntityManager::addEntity(&player, EntityManager::Scenes::GAMEPLAY);
    EntityManager::addEntity(&block, EntityManager::Scenes::FOREGROUND);
    EntityManager::addEntity(&cloud, EntityManager::Scenes::BACKGROUND);

    SpriteManager::addSprite(&player_sprite, SpriteManager::Scenes::GAMEPLAY);
    SpriteManager::addSprite(&block_sprite, SpriteManager::Scenes::FOREGROUND);
    SpriteManager::addSprite(&cloud_sprite, SpriteManager::Scenes::BACKGROUND);

    puts("Birds are Ok, I guess");

    double delta_t = 0;
    glClearColor(0.f, 0.5f, 1.f, 1.f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        delta_t += glfwGetTime();
        glfwSetTime(0);

        while (delta_t > FRAME_TIME) {
            delta_t -= FRAME_TIME;

            glfwPollEvents();
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GL_TRUE);
            }
            player.move(window);

            EntityManager::update(delta_t, EntityManager::Scenes::FOREGROUND);
            EntityManager::update(delta_t, EntityManager::Scenes::GAMEPLAY);
            EntityManager::update(delta_t, EntityManager::Scenes::BACKGROUND);

            player.handleCollision(block, FRAME_TIME);

            EntityManager::sync(EntityManager::Scenes::FOREGROUND);
            EntityManager::sync(EntityManager::Scenes::GAMEPLAY);
            EntityManager::sync(EntityManager::Scenes::BACKGROUND);
        }

        SpriteManager::draw(window, SpriteManager::Scenes::FOREGROUND);
        SpriteManager::draw(window, SpriteManager::Scenes::GAMEPLAY);
        SpriteManager::draw(window, SpriteManager::Scenes::BACKGROUND);


        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
