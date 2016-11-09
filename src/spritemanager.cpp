#include "spritemanager.hpp"

std::array<std::vector<Sprite*>, SpriteManager::NUM_SCENES> SpriteManager::scenes_list = {{}};

void SpriteManager::addSprite(Sprite *sprite, const Scenes scene) {
    scenes_list[scene].push_back(sprite);
}

void SpriteManager::draw(GLFWwindow *window, const Scenes scene) {

    for (auto sprite : scenes_list[scene]) {
        glBindVertexArray(sprite->vao);
        glBindBuffer(GL_ARRAY_BUFFER, sprite->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite->ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    }
}
