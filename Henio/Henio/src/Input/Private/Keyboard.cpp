#include "Input/Public/Keyboard.h"

bool Keyboard::keys[GLFW_KEY_LAST] = { false };
bool Keyboard::keysChanged[GLFW_KEY_LAST] = { false };

void Keyboard::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if (!keys[key])
        {
            keys[key] = true;
        }
    }
    else
    {
        keys[key] = false;
    }

    keysChanged[key] = action != GLFW_REPEAT;
}

bool Keyboard::Key(int key)
{
    return keys[key];
}

bool Keyboard::KeyChanged(int key)
{
    bool ret = keysChanged[key];
    keysChanged[key] = false;
    return ret;
}

bool Keyboard::KeyUp(int key)
{
    return !keys[key] && KeyChanged(key);
}

bool Keyboard::KeyDown(int key)
{
    return keys[key] && KeyChanged(key);
}
