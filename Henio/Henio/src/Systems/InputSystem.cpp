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

        inputComp.mouseX = Mouse::GetMouseX();
        inputComp.mouseY = Mouse::GetMouseY();
        inputComp.mouseDeltaX = Mouse::GetMouseDeltaX();
        inputComp.mouseDeltaY = Mouse::GetMouseDeltaY();
        inputComp.mouseScrollDeltaX = Mouse::scrollDeltaX;
        inputComp.mouseScrollDeltaY = Mouse::scrollDeltaY;
        inputComp.mouseButtons = Mouse::buttons;
        inputComp.mouseButtonsChanged = Mouse::buttonsChanged;
    }
}
