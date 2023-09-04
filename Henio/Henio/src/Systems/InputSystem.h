#pragma once
#include "Core/ECS/Public/Coordinator.h"
#include "Core/ECS/Public/SystemManager.h"

extern ECS::Coordinator coordinator;

class InputSystem : public ECS::System
{
public:
    void Init();
    void Update(float deltaTime);
};
