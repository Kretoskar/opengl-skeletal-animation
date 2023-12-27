#include "Window.h"
#include "Logger.h"

bool Window::Init(unsigned int width, unsigned int height, std::string title)
{
    if (!glfwInit())
    {
        LOG_ERROR("glfwInit() error")
        return false;
    }
    
    /* set a "hint" for the NEXT window created*/
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    
    if (!mWindow)
    {
        LOG_ERROR("Could not create window")
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(mWindow);
    LOG_MESSAGE("Window successfully initialized")

    glfwSetWindowUserPointer(mWindow, this);
    
    glfwSetWindowCloseCallback(mWindow, [](GLFWwindow *win)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleWindowCloseEvents();
    });

    glfwSetWindowIconifyCallback(mWindow, [](GLFWwindow *win, int minimized)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleWindowMinimizedEvents(minimized);
    });

    glfwSetWindowMaximizeCallback(mWindow, [](GLFWwindow *win, int maximized)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleWindowMaximizedEvents(maximized);
    });

    glfwSetKeyCallback(mWindow, [](GLFWwindow *win, int key, int scancode, int action, int mods)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleKeyEvents(key, scancode, action, mods);
    });

    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow *win, int button, int action, int mods)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleMouseButtonEvents(button, action, mods);
    });
    
    return true;
}

void Window::MainLoop()
{
    glfwSwapInterval(1);
    float color = 0.0f;
    
    while (!glfwWindowShouldClose(mWindow))
    {
        color >= 1.0f ? color = 0.0f : color += 0.01f;
        glClearColor(color, color, color, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mWindow);
        
         
        glfwPollEvents();
    }
}

void Window::Cleanup()
{
    LOG_MESSAGE("Terminating Window")
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Window::HandleWindowCloseEvents()
{
    LOG_MESSAGE("Window has been closed")
}

void Window::HandleWindowMinimizedEvents(int minimized)
{
    if (minimized)
    {
        LOG_MESSAGE("Window has been minimized")
    }
    else
    {
        LOG_MESSAGE("Window has been restored")
    }
}

void Window::HandleWindowMaximizedEvents(int maximized)
{
    if (maximized)
    {
        LOG_MESSAGE("Window has been maximized")
    }
    else
    {
        LOG_MESSAGE("Window has been restored")
    }
}

void Window::HandleKeyEvents(int key, int scancode, int action, int mods)
{
    std::string actionName;
    switch (action)
    {
        case GLFW_PRESS:
            actionName = "pressed";
            break;
        case GLFW_RELEASE:
            actionName = "released";
            break;
        case GLFW_REPEAT:
            actionName = "repeated";
            break;
        default:
            actionName = "invalid";
            break;
    }

    const char *keyName = glfwGetKeyName(key, 0);
    LOG_MESSAGE("key %s (key %i, scancode %i) %s", keyName, key, scancode, actionName.c_str())
}

void Window::HandleMouseButtonEvents(int button, int action, int mods)
{
    std::string actionName;
    switch (action)
    {
        case GLFW_PRESS:
            actionName = "pressed";
            break;
        case GLFW_RELEASE:
            actionName = "released";
            break;
        case GLFW_REPEAT:
            actionName = "repeated";
            break;
        default:
            actionName = "invalid";
            break;
    }

    std::string mouseButtonName;
    switch(button)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
            mouseButtonName = "left";
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mouseButtonName = "middle";
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mouseButtonName = "right";
            break;
        default:
            mouseButtonName = "other";
            break;
    }

    LOG_MESSAGE("%s mouse button (%i) %s", mouseButtonName.c_str(), button, actionName.c_str())
}