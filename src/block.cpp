#include "block.hpp"

Block::Block() : Entity() {
    texPosition = {32.f, 32.f};
}
Block::Block(glm::vec2 position) : Entity(position) {
    texPosition = {32.f, 32.f};
}
Block::Block(glm::vec2 position, glm::vec2 size) : Entity(position, size) {
    texPosition = {32.f, 32.f};
}
