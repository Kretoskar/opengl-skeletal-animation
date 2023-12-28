#pragma once

#include <string>
#include <GLFW/glfw3.h>

class Window
{
    
public:
    bool Init(unsigned int width, unsigned int height, std::string title);
    void MainLoop();
    void Cleanup();
    
private:
    void HandleWindowCloseEvents();
    void HandleWindowMinimizedEvents(int minimized);
    void HandleWindowMaximizedEvents(int maximized);

    void HandleKeyEvents(int key, int scancode, int action, int mods);
    void HandleMouseButtonEvents(int button, int action, int mods);
    
    GLFWwindow *mWindow = nullptr;
};