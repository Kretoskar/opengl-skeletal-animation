#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "Rendering/Public/Shader.h"
#include "Input/Public/Keyboard.h"
#include "Input/Public/Mouse.h"
#include "Input/Public/Gamepad.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

glm::mat4 transform = glm::mat4(1.0f);
Gamepad mainGamepad(0);

int main()
{
	glfwInit();
	
	// using 3.3 as it's the doc supported version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	constexpr uint16_t windowWidth = 800;
	constexpr uint16_t windowHeight = 600;

	// make window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Henio", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, windowWidth, windowHeight);
	// init callback for resizing
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	glfwSetKeyCallback(window, Keyboard::KeyCallback);
	glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::MouseWheelCallback);
	
	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");
	
	constexpr float vertices[] =
	{
		//vertices				colors					text coords
		-0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.5f,		0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.5f, 1.0f, 0.75f,		0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		0.6f, 1.0f, 0.2f,		1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 0.2f, 1.0f,		1.0f, 1.0f
	};

	constexpr uint32_t indices[] =
	{
		0, 1, 2,
		3, 1, 2
	};

	// vao, vbo
	uint32_t VAO, VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// set attributes pointers
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// textures
	uint32_t texture1;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// s - x, t - y, r - z
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// load image
	int32_t width, height, nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("assets/kotchuj.jpg", &width, &height, &nChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	
	shader.Activate();
	shader.SetInt("texture1", 0);

	mainGamepad.Update();
	if (mainGamepad.IsPresent())
	{
		std::cout << mainGamepad.GetName() << " is present." << std::endl;
	}
	else
	{
		std::cout << "Gamepad not present" << std::endl;
	}
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);


		glBindVertexArray(VAO);
		
		shader.Activate();
		shader.SetMat4("transform", transform);

		//draw shapes

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, reinterpret_cast<void*>(3 * sizeof(unsigned int)));

		// swap color buffer used to render this render iteration
		// and output it to screen (double buffer doc page 23)
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		// checks for events and updates window state
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (Keyboard::Key(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}

	/*
	if (Keyboard::Key(GLFW_KEY_UP))
	{
		transform = glm::translate(transform, glm::vec3(0.0f, 0.1f, 0.0f));
	}

	if (Keyboard::Key(GLFW_KEY_DOWN))
	{
		transform = glm::translate(transform, glm::vec3(0.0f, -0.1f, 0.0f));
	}

	if (Keyboard::Key(GLFW_KEY_LEFT))
	{
		transform = glm::translate(transform, glm::vec3(-0.1f, 0, 0.0f));
	}

	if (Keyboard::Key(GLFW_KEY_RIGHT))
	{
		transform = glm::translate(transform, glm::vec3(0.1f, 0.0f, 0.0f));
	}
	*/

	
	float lx = mainGamepad.AxisState(GLFW_JOYSTICK_AXES_LEFT_STICK_X);
	float ly = -mainGamepad.AxisState(GLFW_JOYSTICK_AXES_LEFT_STICK_Y);

	if (std::abs(lx) > 0.5f)
	{
		transform = glm::translate(transform, glm::vec3(lx / 10, 0.0f, 0.0f));
	}

	if (std::abs(ly) > 0.5f)
	{
		transform = glm::translate(transform, glm::vec3(0.0f, ly / 10, 0.0f));
	}
	
	mainGamepad.Update();
}
