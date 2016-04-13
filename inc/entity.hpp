#ifndef ENTITY
#define ENTITY

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Entity {
public:
	glm::vec2 size;
	glm::vec2 position;
    glm::vec2 velocity;
	glm::vec2 acceleration;
    float mass;

    void applyForce(glm::vec2 force);
    void update(float delta_t);
    void move(GLFWwindow *window);
	void handleCollision(Entity &e, float delta_time);
    void bounce();
    glm::vec2 momentum();
    bool isColliding(Entity &e);

	Entity();
    Entity(glm::vec2 position);
    Entity(glm::vec2 position, glm::vec2 size);
};

#endif
