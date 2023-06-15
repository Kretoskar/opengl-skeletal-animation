#include "Input/Public/Gamepad.h"

Gamepad::Gamepad(int i)
{
    id = GetId(i);

    Update();
}

void Gamepad::Update()
{
    present = glfwJoystickPresent(id);

    if (present)
    {
        name = glfwGetJoystickName(id);
        axes = glfwGetJoystickAxes(id, &axesCount);
        buttons = glfwGetJoystickButtons(id, &buttonCount);
    }
}

float Gamepad::AxisState(int axis) const
{
    if (present)
    {
        return axes[axis];
    }

    return 0.0f;
}

unsigned char Gamepad::ButtonState(int button) const
{
    return present ? buttons[button] : GLFW_RELEASE;
}

int Gamepad::GetAxesCount() const
{
    return axesCount;
}

int Gamepad::GetButtonCount() const
{
    return buttonCount;
}

bool Gamepad::IsPresent() const
{
    return present;
}

const char* Gamepad::GetName() const
{
    return name;
}

int Gamepad::GetId(int i)
{
    return GLFW_JOYSTICK_1 + i;
}
