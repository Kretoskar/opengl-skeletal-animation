#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
public:
    bool Init(unsigned int width, unsigned int height);
    bool Resize(unsigned int newWidth, unsigned int newHeight);
    void Bind();
    void Unbind();
    void DrawToScreen();
    void Cleanup();
    
private:
    bool CheckComplete();
    
    unsigned int bufferWidth = 640;
    unsigned int bufferHeight = 480;
    GLuint buffer = 0;
    GLuint colorTex = 0;
    GLuint depthBuffer = 0;
};
