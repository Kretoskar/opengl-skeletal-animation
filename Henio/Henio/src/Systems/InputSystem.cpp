#include "InputSystem.h"
#include "Components/Public/InputComponent.h"
#include "Input/Public/Keyboard.h"
#include "Input/Public/Mouse.h"

void InputSystem::Init()
{
}

void InputSystem::Update(float deltaTime)
{
    for (auto const entity : mEntities)
    {
        auto& inputComp = coordinator.GetComponent<InputComponent>(entity);

        inputComp.keyboardKeys = Keyboard::keys;
        inputComp.keyboardKeysChanged = Keyboard::keysChanged;

        inputComp.mouseX = Mouse::x;
        inputComp.mouseY = Mouse::y;
        inputComp.mouseDeltaX = Mouse::deltaX;
        inputComp.mouseDeltaY = Mouse::deltaY;
        inputComp.mouseScrollDeltaX = Mouse::scrollDeltaX;
        inputComp.mouseScrollDeltaY = Mouse::scrollDeltaY;
        inputComp.mouseButtons = Mouse::buttons;
        inputComp.mouseButtonsChanged = Mouse::buttonsChanged;
    }
}
