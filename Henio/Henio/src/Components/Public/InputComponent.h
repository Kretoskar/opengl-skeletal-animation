#pragma once

struct InputComponent
{
    bool* keyboardKeys;
    bool* keyboardKeysChanged;

    double mouseX;
    double mouseY;

    double mouseDeltaX;
    double mouseDeltaY;

    double mouseScrollDeltaX;
    double mouseScrollDeltaY;

    bool* mouseButtons;
    bool* mouseButtonsChanged;

    bool KeyboardKeyUp(int key) const
    {
        return !keyboardKeys[key] && keyboardKeysChanged[key];
    }
    
    bool KeyboardKeyDown(int key) const
    {
        return keyboardKeys[key] && keyboardKeysChanged[key];
    }

    bool MouseButtonUp(int button) const
    {
        return !mouseButtons[button] && mouseButtonsChanged[button];
    }

    bool MouseButtonDown(int button) const
    {
        return mouseButtons[button] && mouseButtonsChanged[button];
    }
};