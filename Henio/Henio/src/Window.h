#pragma once

#include <string>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "Model.h"


class Window
{
    
public:
    bool Init(unsigned int width, unsigned int height, std::string title);
    void MainLoop();
    void Cleanup();

    GLFWwindow* GetGLFWWindow() const { return window; }
    
private:
    void HandleWindowCloseEvents();
    void HandleWindowMinimizedEvents(int minimized);
    void HandleWindowMaximizedEvents(int maximized);

    void HandleKeyEvents(int key, int scancode, int action, int mods);
    void HandleMouseButtonEvents(int button, int action, int mods);
    
    GLFWwindow* window = nullptr;

    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Model> model;
};