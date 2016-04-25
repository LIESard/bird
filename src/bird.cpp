#include "bird.hpp"

Bird::Bird() : Entity() {
    texPosition = {0.f, 0.f};
}
Bird::Bird(glm::vec2 position) : Entity(position) {
    texPosition = {0.f, 0.f};
}
Bird::Bird(glm::vec2 position, glm::vec2 size) : Entity(position, size) {
    texPosition = {0.f, 0.f};
}
