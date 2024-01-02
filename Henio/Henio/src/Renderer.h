#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Framebuffer.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderData.h"

class Renderer
{
public:
    bool Init(unsigned int width, unsigned int height);
    void SetSize(unsigned int width, unsigned int height);
    void Cleanup();
    void UploadData(Mesh vertexData);
    void Draw();
    
private:
    Shader basicShader;
    Framebuffer frameBuffer;
    VertexBuffer vertexBuffer;
    Texture tex;
    int triangleCount = 0;
};
