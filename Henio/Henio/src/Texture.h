#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
    bool LoadTexture(std::string textureFilename);
    void Bind();
    void Unbind();
    void Cleanup();

private:
    GLuint texture = 0;
};
