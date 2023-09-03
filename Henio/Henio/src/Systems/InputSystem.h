#pragma once
#include "Components/Public/InputComponent.h"
#include "Core/ECS/Public/Coordinator.h"
#include "Core/ECS/Public/SystemManager.h"
#include "Input/Public/Keyboard.h"

extern ECS::Coordinator coordinator;

class InputSystem : public ECS::System
{
public:
    void Init()
    {
    }
    
    void Update(float deltaTime)
    {
        for (auto const entity : mEntities)
        {
            auto& inputComp = coordinator.GetComponent<InputComponent>(entity);

            inputComp.keyboardKeys = Keyboard::keys;
            
        }
    }
};
