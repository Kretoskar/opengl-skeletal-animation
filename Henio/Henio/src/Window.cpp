#include "Window.h"
#include "Logger.h"

bool Window::Init(unsigned int width, unsigned int height, std::string title)
{
    if (!glfwInit())
    {
        LOG_ERROR("glfwInit() error")
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* set a "hint" for the NEXT window created*/
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    
    if (!window)
    {
        LOG_ERROR("Could not create window")
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    LOG_MESSAGE("Window successfully initialized")

    glfwSetWindowUserPointer(window, this);
    
    glfwSetWindowCloseCallback(window, [](GLFWwindow *win)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleWindowCloseEvents();
    });

    glfwSetWindowIconifyCallback(window, [](GLFWwindow *win, int minimized)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleWindowMinimizedEvents(minimized);
    });

    glfwSetWindowMaximizeCallback(window, [](GLFWwindow *win, int maximized)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleWindowMaximizedEvents(maximized);
    });

    glfwSetKeyCallback(window, [](GLFWwindow *win, int key, int scancode, int action, int mods)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleKeyEvents(key, scancode, action, mods);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *win, int button, int action, int mods)
    {
        const auto w = static_cast<Window*>(glfwGetWindowUserPointer(win));
        w->HandleMouseButtonEvents(button, action, mods);
    });
    
    renderer = std::make_unique<Renderer>();
    if (!renderer->Init(width, height))
    {
        glfwTerminate();
        LOG_ERROR("Could not init OpenGL renderer")
        return false;
    }

    glfwSetWindowUserPointer(window, renderer.get());
    glfwSetWindowSizeCallback(window, [](GLFWwindow *win, int width, int height)
    {
      auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
      renderer->SetSize(width, height);
    });

    model = std::make_unique<Model>();
    model->Init();

    LOG_MESSAGE("Window with OpenGL 4.6 successfully initialized")
    return true;
}

void Window::MainLoop()
{
    /* force VSYNC */
    glfwSwapInterval(1);

    /* upload only once for now */
    renderer->UploadData(model->GetVertexData());

    while (!glfwWindowShouldClose(window)) {
        renderer->Draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::Cleanup()
{
    LOG_MESSAGE("Terminating Window")
    glfwDestroyWindow(window);
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