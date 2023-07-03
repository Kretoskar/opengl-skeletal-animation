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
public:
	Shader();
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void Generate(const char* vertexShaderPath, const char* fragmentShaderPath);
	
	static GLuint CompileShader(const char* filepath, GLenum type);
	static std::string LoadShaderSrc(const char* filepath);

	uint32_t id;
	
	void Activate() const;

	void SetBool(const std::string& name, bool value);
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);
	void Set3Float(const std::string& name, float v1, float v2, float v3);
	void Set3Float(const std::string& name, glm::vec3 v);
	void Set4Float(const std::string& name, float v1, float v2, float v3, float v4);
	void Set4Float(const std::string& name, glm::vec4 v);
	void SetMat3(const std::string& name, glm::mat3 val);
	void SetMat4(const std::string& name, glm::mat4 val);
};

