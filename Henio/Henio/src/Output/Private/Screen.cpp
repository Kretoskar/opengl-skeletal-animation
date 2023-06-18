#include "Output/Public/Screen.h"

#include "Input/Public/Keyboard.h"
#include "Input/Public/Mouse.h"

uint16_t Screen::SCR_WIDTH = 800;
uint16_t Screen::SCR_HEIGHT = 600;
const char* Screen::APP_NAME = "Henio Game Engine";

void Screen::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

Screen::Screen()
    : window(nullptr)
{
}

bool Screen::Init()
{
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, APP_NAME, nullptr, nullptr);

    if (!window)
    {
        return false;
    }

    glfwMakeContextCurrent(window);
    return true;
}

void Screen::SetParameters()
{
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glfwSetFramebufferSizeCallback(window, Screen::FrameBufferSizeCallback);

    glfwSetKeyCallback(window, Keyboard::KeyCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Mouse::CursorPoseCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::MouseWheelCallback);

    glEnable(GL_DEPTH_TEST);
}

void Screen::Update()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::NewFrame()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Screen::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Screen::SetShouldClose(bool shouldClose)
{
    glfwSetWindowShouldClose(window, shouldClose);
}
