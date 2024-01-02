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

    int texWidth = 0;
    int texHeight = 0;
    int nChannels = 0;
    std::string textureName;
};
