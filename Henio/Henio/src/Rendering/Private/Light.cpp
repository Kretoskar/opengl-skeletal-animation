#include "Rendering/Public/Light.h"

void PointLight::Render(int idx, Shader shader)
{
    const std::string name = "pointLights[" + std::to_string(idx) + "]";
    
    shader.Set3Float(name + ".position", position);

    shader.SetFloat(name + ".k0", k0);
    shader.SetFloat(name + ".k1", k1);
    shader.SetFloat(name + ".k2", k2);
    
    shader.Set3Float(name + ".ambient", ambient);
    shader.Set3Float(name + ".diffuse", diffuse);
    shader.Set3Float(name + ".specular", specular);
}

void DirLight::Render(Shader shader)
{
    const std::string name = "dirLight";
    
    shader.Set3Float(name + ".direction", direction);
    shader.Set3Float(name + ".ambient", ambient);
    shader.Set3Float(name + ".diffuse", diffuse);
    shader.Set3Float(name + ".specular", specular);
}

void SpotLight::Render(int idx, Shader shader)
{
    const std::string name = "spotLights["+ std::to_string(idx) + "]";
    
    shader.Set3Float(name + ".position", position);
    shader.Set3Float(name + ".direction", direction);

    shader.SetFloat(name + ".k0", k0);
    shader.SetFloat(name + ".k1", k1);
    shader.SetFloat(name + ".k2", k2);
    
    shader.SetFloat(name + ".cutOff", cutOff);
    shader.SetFloat(name + ".outerCutOff", outerCutOff);

    shader.Set3Float(name + ".ambient", ambient);
    shader.Set3Float(name + ".diffuse", diffuse);
    shader.Set3Float(name + ".specular", specular);
}
