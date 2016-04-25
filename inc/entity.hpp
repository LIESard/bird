#ifndef ENTITY
#define ENTITY

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <array>

class Entity {
public:
    glm::vec2 size;
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    float mass;
    glm::vec2 texPosition;
    glm::vec2 texSize = {16.f, 16.f};

    std::array<float, 16> vertices;

    virtual void applyForce(glm::vec2 force);
    virtual void update(float delta_t);
    virtual void move(GLFWwindow *window);
    virtual void handleCollision(Entity &e, float delta_time);
    virtual void bounce();
    virtual glm::vec2 momentum();
    virtual bool isColliding(Entity &e);

    Entity();
    Entity(glm::vec2 position);
    Entity(glm::vec2 position, glm::vec2 size);
};

#endif
