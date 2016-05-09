#ifndef CLOUD
#define CLOUD

#include "entity.hpp"

class Cloud : public Entity {
public:
    Cloud();
    Cloud(glm::vec2 position);
    Cloud(glm::vec2 position, glm::vec2 size);
};

#endif