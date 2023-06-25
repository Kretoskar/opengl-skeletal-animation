#pragma once

#include "Cube.hpp"
#include "Rendering/Public/Light.h"

class Lamp : public Cube
{
public:
    Lamp(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& lightColor,
        const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : Cube(Material::white_plastic, pos, size),
          lightColor(lightColor),
          pointLight({pos, ambient, diffuse, specular})
    {
    }

    void Render(Shader shader) override
    {
        shader.Set3Float("lightColor", lightColor);

        Cube::Render(shader);
    }
    
    glm::vec3 lightColor;

    PointLight pointLight;
};
