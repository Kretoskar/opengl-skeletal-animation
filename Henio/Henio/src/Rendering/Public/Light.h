#pragma once

#include <glm/glm.hpp>

#include "Rendering/Public/Shader.h"

struct PointLight
{
    glm::vec3 position;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    void Render(Shader shader);
};

class Light
{
public:
    
};
