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

        /* swap buffers */
        glfwSwapBuffers(mWindow);
        
        /* poll events in a loop */
        glfwPollEvents();
        
    }
}

void Window::Cleanup()
{
    LOG_MESSAGE("Terminating Window")
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}