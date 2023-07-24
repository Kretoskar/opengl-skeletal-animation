#pragma once

#include "Components/Public/TransformComponent.h"
#include "Core/ECS/Public/Coordinator.h"
#include "Core/ECS/Public/SystemManager.h"

extern ECS::Coordinator coordinator;

class MoveRightSystem : public ECS::System
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

            transform.position.x += deltaTime;
        }
    }
};