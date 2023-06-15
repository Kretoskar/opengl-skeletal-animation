#include "Input/Public/Mouse.h"

double Mouse::x = 0;
double Mouse::y = 0;

double Mouse::lastX = 0;
double Mouse::lastY = 0;
double Mouse::deltaX = 0;
double Mouse::deltaY = 0;

double Mouse::scrollDeltaX = 0;
double Mouse::scrollDeltaY = 0;

bool Mouse::firstMouse = 0;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { false };
bool Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = { false };

void Mouse::CursorPoseCallback(GLFWwindow* window, double _x, double _y)
{
    x = _x;
    y = _y;

    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    deltaX = x - lastX;
    deltaY = lastY - y;
    lastX = x;
    lastY = y;
}

void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
        if (!buttons[button])
        {
            buttons[button] = true;
        }
    }
    else
    {
        buttons[button] = false;
    }

    buttonsChanged[button] = action != GLFW_REPEAT;
}

void Mouse::MouseWheelCallback(GLFWwindow* window, double dx, double dy)
{
    scrollDeltaX = dx;
    scrollDeltaY = dy;
}

double Mouse::GetMouseX()
{
    return x;
}

double Mouse::GetMouseY()
{
    return y;
}

double Mouse::GetMouseDeltaX()
{
    const double dx = deltaX;
    deltaX = 0;
    return dx;
}

double Mouse::GetMouseDeltaY()
{
    const double dy = deltaY;
    deltaY = 0;
    return dy;
}

double Mouse::GetScrollDeltaX()
{
    const double dx = scrollDeltaX;
    scrollDeltaX = 0;
    return dx;
}

double Mouse::GetScrollDeltaY()
{
    const double dy = scrollDeltaY;
    scrollDeltaY = 0;
    return dy;
}

bool Mouse::Button(int button)
{
    return buttons[button];
}

bool Mouse::ButtonChanged(int button)
{
    bool ret = buttonsChanged[button];
    buttonsChanged[button] = false;
    return ret;
}

bool Mouse::ButtonUp(int button)
{
    return !buttons[button] && ButtonChanged(button);
}

bool Mouse::ButtonDown(int button)
{
    return buttons[button] && ButtonChanged(button);
}
