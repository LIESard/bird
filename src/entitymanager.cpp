#include "entitymanager.hpp"

std::array<std::vector<Entity*>, EntityManager::NUM_SCENES>
        EntityManager::scenes_list = {{}};

void EntityManager::addEntity(Entity *entity, const Scenes scene) {
    scenes_list[scene].push_back(entity);
}

void EntityManager::update(float delta_t, const Scenes scene) {
    for (auto entity : scenes_list[scene]) {
        entity->update(delta_t);
    }
}

void EntityManager::sync(const Scenes scene) {
    for (unsigned int i = 0; i < scenes_list[scene].size(); i++) {
        SpriteManager::scenes_list[scene][i]->sync(*scenes_list[scene][i]);
    }
}
