#include "cloud.hpp"

Cloud::Cloud() : Entity() {
    texPosition = {0.f, 32.f};
    texSize = {32.f, 16.f};
}
Cloud::Cloud(glm::vec2 position) : Entity(position) {
    size = {128, 64};
    texPosition = {0.f, 32.f};
    texSize = {32.f, 16.f};
}
Cloud::Cloud(glm::vec2 position, glm::vec2 size) : Entity(position, size) {
    size = {128, 64};
    texPosition = {0.f, 32.f};
    texSize = {32.f, 16.f};
}
