#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include <vector>
#include <array>
#include "spritemanager.hpp"
#include "entity.hpp"

class EntityManager {
public:
    enum Scenes {
        GAMEPLAY = 0,
        FOREGROUND,
        BACKGROUND,
        NUM_SCENES
    };

private:
    static std::array<std::vector<Entity*>, NUM_SCENES> scenes_list;

public:
    static void addEntity(Entity *e, const Scenes scene);
    static void update(float delta_t, const Scenes scene);
    static void sync(const Scenes scene);
};

#endif
