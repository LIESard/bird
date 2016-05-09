#ifndef BLOCK
#define BLOCK

#include "entity.hpp"

class Block : public Entity {
public:
    Block();
    Block(glm::vec2 position);
    Block(glm::vec2 position, glm::vec2 size);
};

#endif
