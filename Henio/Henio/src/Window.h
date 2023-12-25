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
    GLFWwindow *mWindow = nullptr;
};