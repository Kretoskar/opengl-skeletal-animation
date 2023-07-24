#pragma once

#include <iostream>

#include "Components/Public/TransformComponent.h"
#include "Core/ECS/Public/Coordinator.h"
#include "Core/ECS/Public/SystemManager.h"

extern ECS::Coordinator coordinator;

class LogTransformSystem : public ECS::System
{
public:
    void Init()
    {
    }
    void Update(float deltaTime)
    {
        for (auto const entity : mEntities)
        {
            auto& transform = coordinator.GetComponent<TransformComponent>(entity);

            std::cout << transform.position.x << std::endl; 
        }
    }
};