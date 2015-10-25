#include "entity.hpp"

void Entity::applyForce(glm::vec2 force) {
    acceleration = force / mass;
}

void Entity::update(float delta_time) {
    velocity += acceleration * delta_time;
    position += velocity * delta_time;
    acceleration = {0, 0};
}

void Entity::move(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (velocity.x < 0) {
            velocity.x = 0;
        }
        acceleration.x = 500;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (velocity.x > 0) {
            velocity.x = 0;
        }
        acceleration.x = -500;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS) {
            velocity.x = 0;
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (velocity.y < 0) {
            velocity.y = 0;
        }
        acceleration.y = 500;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (velocity.y > 0) {
            velocity.y = 0;
        }
        acceleration.y = -500;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS) {
            velocity.y = 0;
    }
}

void Entity::handleCollision(Entity &e, float delta_time) {
    switch (e.type) {
    case BLOCK:
        while (isColliding(e)) {
            position -= velocity * (delta_time / 100.f);
        }
        break;

    case BOUNCE:
        if (isColliding(e)) {
            bounce();
            e.bounce();
        }
        break;

    case BLANK:
        break;

    default:
        break;
    }
}

void Entity::bounce() {
    velocity = -velocity;
}

glm::vec2 Entity::momentum() {
    return mass * velocity;
}

bool Entity::isColliding(Entity &e) {
    return (position.x <= e.position.x + e.size.x &&
            position.x + size.x >= e.position.x &&
            position.y <= e.position.y + e.size.y &&
            position.y + size.y >= e.position.y);
}

Entity::Entity() {}

Entity::Entity(glm::vec2 position) :
               position {position} {}

Entity::Entity(glm::vec2 position, Type type) :
               position {position},
               type {type} {}

Entity::Entity(glm::vec2 position, glm::vec2 size) :
               size {size},
               position {position} {}

Entity::Entity(glm::vec2 position, glm::vec2 size, Type type) :
               size {size},
               position {position},
               type {type} {}
