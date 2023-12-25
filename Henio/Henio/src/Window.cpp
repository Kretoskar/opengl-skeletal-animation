#include "Window.h"
#include "Logger.h"

bool Window::Init(unsigned int width, unsigned int height, std::string title)
{
    if (!glfwInit())
    {
        Logger::LogError("%s: glfwInit() error\n", __FUNCTION__);
        return false;
    }
    
    /* set a "hint" for the NEXT window created*/
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    
    if (!mWindow)
    {
        Logger::LogError("%s: Could not create window\n", __FUNCTION__);
        glfwTerminate();
        return false;
    }
    
    Logger::LogError("%s: Window successfully initialized\n",__FUNCTION__);
    return true;
}

void Window::MainLoop()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        /* poll events in a loop */
        glfwPollEvents();
    }
}

void Window::Cleanup()
{
    Logger::LogMessage("%s: Terminating Window\n", __FUNCTION__);
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}