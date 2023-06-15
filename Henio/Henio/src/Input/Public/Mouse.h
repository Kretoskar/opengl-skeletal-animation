#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Mouse
{
public:
    static void CursorPoseCallback(GLFWwindow* window, double _x, double _y);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseWheelCallback(GLFWwindow* window, double dx, double dy);

    static double GetMouseX();
    static double GetMouseY();

    static double GetMouseDeltaX();
    static double GetMouseDeltaY();

    static double GetScrollDeltaX();
    static double GetScrollDeltaY();

    static bool Button(int button);
    static bool ButtonChanged(int button);
    static bool ButtonUp(int button);
    static bool ButtonDown(int button);

private:
    static double x;
    static double y;

    static double lastX;
    static double lastY;

    static double deltaX;
    static double deltaY;

    static double scrollDeltaX;
    static double scrollDeltaY;

    static bool firstMouse;

    static bool buttons[];
    static bool buttonsChanged[];
    
};
