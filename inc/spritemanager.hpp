#ifndef SPRITEMANAGER
#define SPRITEMANAGER

#include <vector>
#include <array>
#include "sprite.hpp"

class SpriteManager {
public:
    enum Scenes {
        GAMEPLAY = 0,
        FOREGROUND,
        BACKGROUND,
        NUM_SCENES
    };

    static std::array<std::vector<Sprite*>, NUM_SCENES> scenes_list;
    
    static void addSprite(Sprite *sprite, const Scenes scene);
    static void draw(GLFWwindow *window, const Scenes scene);
    static std::array<std::vector<Sprite*>, NUM_SCENES> getScenesList();
};

#endif
