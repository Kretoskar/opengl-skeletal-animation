#include "Shader.h"
#include <fstream>
#include "Shader.h"

#include "Logger.h"

bool Shader::LoadShaders(std::string vertexShaderFileName, std::string fragmentShaderFileName)
{
    const GLuint vertexShader = ReadShader(vertexShaderFileName, GL_VERTEX_SHADER);
    if (!vertexShader)
    {
        LOG_ERROR("Failed to load vertex shader: %s", vertexShaderFileName)
        return false;
    }

    const GLuint fragmentShader = ReadShader(fragmentShaderFileName, GL_FRAGMENT_SHADER);
    if (!fragmentShader)
    {
        LOG_ERROR("Failed to load fragment shader: %s", fragmentShaderFileName)
        return false;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint isProgramLinked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isProgramLinked);
    if (!isProgramLinked)
    {
        LOG_ERROR("Linking shader failed")
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void Shader::Use()
{
    glUseProgram(shaderProgram);
}

void Shader::Cleanup()
{
    glDeleteProgram(shaderProgram);
}

GLuint Shader::ReadShader(std::string shaderFileName, GLuint shaderType)
{
    std::string shaderAsText;
    std::ifstream inFile(shaderFileName);

    if (inFile.is_open())
    {
        inFile.seekg(0, std::ios::end);
        shaderAsText.reserve(inFile.tellg());
        inFile.seekg(0, std::ios::beg);
        shaderAsText.assign((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();
    }
    else
    {
        return 0;
    }

    if (inFile.bad() || inFile.fail())
    {
        inFile.close();
        return 0;
    }
    inFile.close();

    const char* shaderSource = shaderAsText.c_str();
    
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const GLchar**) &shaderSource, nullptr);
    glCompileShader(shader);

    GLint isShaderCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isShaderCompiled);
    if (!isShaderCompiled)
    {
        LOG_ERROR("Failed to compile shader: %s", shaderFileName)
        return 0;
    }

    return shader;
}
