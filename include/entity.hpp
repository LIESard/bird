#ifndef ENTITY
#define ENTITY

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum Type {
    BLOCK,
    BOUNCE,
    BLANK
};

class Entity {
public:
	glm::vec2 size;
	glm::vec2 position;
    glm::vec2 velocity;
	glm::vec2 acceleration;
    float mass;
    Type type;

    void applyForce(glm::vec2 force);
    void update(float delta_t);
    void move(GLFWwindow *window);
	void handleCollision(Entity &e, float delta_time);
    void bounce();
    glm::vec2 momentum();
    bool isColliding(Entity &e);

	Entity();
    Entity(glm::vec2 position);
	Entity(glm::vec2 position, Type type);
    Entity(glm::vec2 position, glm::vec2 size);
	Entity(glm::vec2 position, glm::vec2 size, Type type);
};

#endif
