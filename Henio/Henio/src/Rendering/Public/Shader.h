#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
	uint32_t id;

public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	static GLuint compileShader(const char* filepath, GLenum type);
	static std::string loadShaderSrc(const char* filepath);
	
	void activate() const;
	void setMat4(const std::string& name, glm::mat4 val);
};

