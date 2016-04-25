#ifndef BIRD
#define BIRD

#include <glm/glm.hpp>
#include "entity.hpp"

class Bird : public Entity {
public:
    glm::vec2 texPosition = {0.f, 0.f};

    Bird();
    Bird(glm::vec2 position);
    Bird(glm::vec2 position, glm::vec2 size);
};

#endif
