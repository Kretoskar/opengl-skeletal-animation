#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    bool LoadShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName);
    void Use();
    void Cleanup();

private:
    GLuint ReadShader(std::string shaderFileName, GLuint shaderType);

    GLuint shaderProgram = 0;
};