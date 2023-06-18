#pragma once

#include "Cube.hpp"

class Lamp : public Cube
{
public:
    Lamp(const glm::vec3& pos, const glm::vec3& size, const glm::vec3& lightColor,
        const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : Cube(Material::white_plastic, pos, size),
          lightColor(lightColor),
          ambient(ambient),
          diffuse(diffuse),
          specular(specular)
    {
    }

    void Render(Shader shader) override
    {
        shader.Set3Float("lightColor", lightColor);

        Cube::Render(shader);
    }
    
    glm::vec3 lightColor;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
};