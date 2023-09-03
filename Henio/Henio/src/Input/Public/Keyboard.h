#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Keyboard
{
public:
    static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

    static bool Key(int key);
    static bool KeyChanged(int key);
    static bool KeyUp(int key);
    static bool KeyDown(int key);
    
    static bool keys[];
    static bool keysChanged[];
};