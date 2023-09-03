#include "Output/Public/HenioCore.h"

#include <iostream>

#include "Input/Public/Keyboard.h"
#include "Input/Public/Mouse.h"

uint16_t HenioCore::SCR_WIDTH = 800;
uint16_t HenioCore::SCR_HEIGHT = 600;
const char* HenioCore::APP_NAME = "Henio Game Engine";

void HenioCore::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

HenioCore::HenioCore()
    : window(nullptr)
{
}

bool HenioCore::Init()
{
    glfwInit();
	
    // using 3.3 as it's the doc supported version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!MakeWindow())
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
    }

    // init GLAD
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return false;
    }

    SetParameters();
}

bool HenioCore::MakeWindow()
{
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, APP_NAME, nullptr, nullptr);

    if (!window)
    {
        return false;
    }

    glfwMakeContextCurrent(window);
    return true;
}

void HenioCore::SetParameters()
{
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glfwSetFramebufferSizeCallback(window, HenioCore::FrameBufferSizeCallback);

    glfwSetKeyCallback(window, Keyboard::KeyCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Mouse::CursorPoseCallback);
    glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::MouseWheelCallback);

    glEnable(GL_DEPTH_TEST);
}

void HenioCore::Update()
{
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void HenioCore::NewFrame()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool HenioCore::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void HenioCore::SetShouldClose(bool shouldClose)
{
    glfwSetWindowShouldClose(window, shouldClose);
}
