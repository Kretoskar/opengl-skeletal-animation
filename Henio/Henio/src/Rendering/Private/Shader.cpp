#include "Rendering/Public/Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    int32_t success;

    const GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
    const GLuint fragShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cout << "Linking shaders error: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

GLuint Shader::compileShader(const char* filepath, GLenum type)
{
    int success;

    GLuint ret = glCreateShader(type);
    std::string shaderSrc = loadShaderSrc(filepath);
    const GLchar* shader = shaderSrc.c_str();
    glShaderSource(ret, 1, &shader, nullptr);
    glCompileShader(ret);

    glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(ret, 512, nullptr, infoLog);
        std::cout << "Vertex shader error: " << infoLog << std::endl;
    }

    return ret;
}

std::string Shader::loadShaderSrc(const char* filepath)
{
    std::ifstream file;

    std::string ret;

    file.open(filepath);

    if (file.is_open())
    {
        std::stringstream buf;
        buf << file.rdbuf();
        ret = buf.str();
    }
    else
    {
        std::cout << "Couldn't open file: " << filepath << std::endl;
    }

    file.close();

    return ret;
}

void Shader::activate() const
{
    glUseProgram(id);
}

void Shader::setMat4(const std::string& name, glm::mat4 val)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}
