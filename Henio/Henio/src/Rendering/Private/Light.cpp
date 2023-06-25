#include "Rendering/Public/Light.h"

void PointLight::Render(Shader shader)
{
    std::string name = "pointLight";
    
    shader.Set3Float(name + ".position", position);
    shader.Set3Float(name + ".ambient", ambient);
    shader.Set3Float(name + ".diffuse", diffuse);
    shader.Set3Float(name + ".specular", specular);
}
