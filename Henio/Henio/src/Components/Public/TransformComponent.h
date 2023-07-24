#pragma once
#include <glm/vec3.hpp>

struct TransformComponent
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};