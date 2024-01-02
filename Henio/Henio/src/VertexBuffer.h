#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "RenderData.h"

class VertexBuffer
{
public:
    void Init();
    void UploadData(Mesh vertexData);
    void Bind();
    void Unbind();
    void Draw(GLuint mode, unsigned int start, unsigned int num);
    void Cleanup();

private:
    GLuint VAO = 0;
    GLuint vertexVBO = 0;
};