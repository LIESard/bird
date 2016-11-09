#include "entity.hpp"

void Entity::applyForce(glm::vec2 force) {
    acceleration = force / mass;
}

void Entity::update(float delta_time) {
    velocity += acceleration * delta_time;
    position += velocity * delta_time;
    // acceleration = {0, 0};
    
    vertices = {{
        // position coordinates
        // texture coordinates
        position.x, position.y,
        texPosition.x, texPosition.y + texSize.y,

        position.x + size.x, position.y,
        texPosition.x + texSize.x, texPosition.y + texSize.y,

        position.x + size.x, position.y + size.y,
        texPosition.x + texSize.x, texPosition.y,

        position.x, position.y + size.y,
        texPosition.x, texPosition.y,
    }};
}

void Entity::move(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (velocity.x != 5000) {
            acceleration.x = 5000;
        } else {
            acceleration.x = 0;
        }
        velocity.x = 5000;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (velocity.x != -5000) {
            acceleration.x = -5000;
        } else {
            acceleration.x = 0;
        }
        velocity.x = -5000;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS) {
            acceleration.x = -(5 * velocity.x);
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (velocity.y != 5000) {
            acceleration.y = 5000;
        } else {
            acceleration.y = 0;
        }
        velocity.y = 5000;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (velocity.y != -5000) {
            acceleration.y = -5000;
        } else {
            acceleration.y = 0;
        }
        velocity.y = -5000;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_PRESS) {
            acceleration.y = -(5 * velocity.y);
    }
}

void Entity::handleCollision(Entity &e, float delta_time) {}

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
               position {position} {
                size = {64, 64};
               }

Entity::Entity(glm::vec2 position, glm::vec2 size) :
               size {size},
               position {position} {

    vertices = {{
        // position coordinates                             texture coordinates
        position.x, position.y,
        texPosition.x, texPosition.y + texSize.y,

        position.x + size.x, position.y,
        texPosition.x + texSize.x, texPosition.y + texSize.y,

        position.x + size.x, position.y + size.y,
        texPosition.x + texSize.x, texPosition.y,

        position.x, position.y + size.y,
        texPosition.x, texPosition.y,
    }};
}
