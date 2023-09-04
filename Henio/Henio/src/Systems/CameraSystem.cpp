#include "CameraSystem.h"

#include <GLFW/glfw3.h>

#include "Components/Public/CameraComponent.h"
#include "Components/Public/InputComponent.h"
#include "Components/Public/TransformComponent.h"
#include "Rendering/Models/Public/Lamp.hpp"

void CameraSystem::Init()
{
    for (auto const entity : mEntities)
    {
        auto& transformComponent = coordinator.GetComponent<TransformComponent>(entity);
        auto& inputComponent = coordinator.GetComponent<InputComponent>(entity);

        transformComponent.rotation = glm::vec3(0, -90.0f, 0);
    }
}

void CameraSystem::Update(float deltaTime)
{
    for (auto const entity : mEntities)
    {
        auto& cameraComponent = coordinator.GetComponent<CameraComponent>(entity);
        auto& transformComponent = coordinator.GetComponent<TransformComponent>(entity);
        auto& inputComponent = coordinator.GetComponent<InputComponent>(entity);

        float velocity = deltaTime * cameraComponent.speed;
        
        ProcessKeyboardInput(transformComponent, inputComponent, velocity);
        ProcessMouseInput(transformComponent, inputComponent);

        CamTransformComp = transformComponent;
    }
}

void CameraSystem::ProcessKeyboardInput(TransformComponent& transformComponent, InputComponent& inputComponent, float velocity)
{
    if (inputComponent.keyboardKeys[GLFW_KEY_W])
    {
        transformComponent.position += transformComponent.GetFrontVector() * velocity;
    }
    else if (inputComponent.keyboardKeys[GLFW_KEY_S])
    {
        transformComponent.position -= transformComponent.GetFrontVector() * velocity;
    }
    else if (inputComponent.keyboardKeys[GLFW_KEY_A])
    {
        transformComponent.position -= transformComponent.GetRightVector() * velocity;
    }
    else if (inputComponent.keyboardKeys[GLFW_KEY_D])
    {
        transformComponent.position += transformComponent.GetRightVector() * velocity;
    }
    else if (inputComponent.keyboardKeys[GLFW_KEY_SPACE])
    {
        transformComponent.position += transformComponent.GetUpVector() * velocity;
    }
    else if (inputComponent.keyboardKeys[GLFW_KEY_LEFT_SHIFT])
    {
        transformComponent.position -= transformComponent.GetUpVector() * velocity;
    }
}

void CameraSystem::ProcessMouseInput(TransformComponent& transformComponent, InputComponent& inputComponent)
{
    transformComponent.rotation.y += inputComponent.mouseDeltaX;
    transformComponent.rotation.x += inputComponent.mouseDeltaY;
    transformComponent.rotation.x = glm::clamp(transformComponent.rotation.x, -89.0f, 89.0f);
}