#include "Renderer.h"

#include "Logger.h"
#include "Window.h"

Renderer::Renderer(Window* window)
{
    renderData.window = window;
}

bool Renderer::Init(unsigned width, unsigned height)
{
    renderData.width = width;
    renderData.height = height;
    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        LOG_ERROR("GLLoader failed to load")
        return false;
    }
    
    if (!GLAD_GL_VERSION_4_6)
    {
        LOG_ERROR("GLAD GL version not 4.6")
        return false;
    }
    
    if (!frameBuffer.Init(width, height))
    {
        LOG_ERROR("Failed to init framebuffer")
        return false;
    }

    if (!tex.LoadTexture( "Assets/Textures/crate.png"))
    {
        LOG_ERROR("Failed to load texture")
        return false;
    }

    vertexBuffer.Init();
    
    if (!basicShader.LoadShaders( "Shaders/basic.vert", "Shaders/basic.frag"))
    {
        LOG_ERROR("Failed to load shader")
        return false;
    }

    if (!changedShader.LoadShaders( "Shaders/changed.vert", "Shaders/changed.frag"))
    {
        LOG_ERROR("Failed to load shader")
        return false;
    }

    userInterface.Init(renderData);
    return true;
}

void Renderer::SetSize(unsigned width, unsigned height)
{
    renderData.width = width;
    renderData.height = height;
    frameBuffer.Resize(width, height);
    glViewport(0, 0, width, height);
}

void Renderer::Cleanup()
{
    basicShader.Cleanup();
    changedShader.Cleanup();
    tex.Cleanup();
    vertexBuffer.Cleanup();
    frameBuffer.Cleanup();
    userInterface.Cleanup();
}

void Renderer::UploadData(Mesh vertexData)
{
    renderData.triangleCount = vertexData.vertices.size() / 3;
    vertexBuffer.UploadData(vertexData);
}

void Renderer::Draw()
{
    // bind framebuffer to let it receive vertex data
    frameBuffer.Bind();
    // draw background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);

    if (useChangedShader)
    {
        changedShader.Use();
    } else
    {
        basicShader.Use();
    }
    
    tex.Bind();
    vertexBuffer.Bind();
    vertexBuffer.Draw(GL_TRIANGLES, 0, renderData.triangleCount * 3);
    vertexBuffer.Unbind();
    tex.Unbind();
    frameBuffer.Unbind();

    frameBuffer.DrawToScreen();
    userInterface.CreateFrame(renderData);
    userInterface.Render();
}

void Renderer::HandleKeyEvents(int key, int scancode, int action, int mods)
{
    if (glfwGetKey(renderData.window->GetGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        useChangedShader = !useChangedShader;
    }
}
