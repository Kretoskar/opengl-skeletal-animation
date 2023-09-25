#pragma once
#include "Components/Public/InputComponent.h"
#include "Components/Public/TransformComponent.h"
#include "Core/ECS/Public/Coordinator.h"
#include "Core/ECS/Public/SystemManager.h"

extern ECS::Coordinator coordinator;

class CameraSystem : public ECS::System
{
public:
    void Init();
    void ProcessKeyboardInput(TransformComponent& transformComponent, InputComponent& inputComponent, float speed);
    void ProcessMouseInput(TransformComponent& transformComponent, InputComponent& inputComponent, float speed);
    void Update(float deltaTime);

    TransformComponent CamTransformComp;
};
