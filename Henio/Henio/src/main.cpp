#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Rendering/Public/Shader.h"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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

	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");
	
	float vertices[] =
	{
		//vertices				colors
		-0.25f, -0.5f, 0.0f,	1.0f, 1.0f, 0.5f,
		0.15f, 0.0f, 0.0f,		0.5f, 1.0f, 0.75f,
		0.0f, 0.5f, 0.0f,		0.6f, 1.0f, 0.2f,
		0.5f, -0.4f, 0.0f,		1.0f, 0.2f, 1.0f
	};

	uint32_t indices[] =
	{
		0, 1, 2,
		3, 1, 2
	};


	// vao, vbo
	uint32_t VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set attribute pointers

	//positions
	glVertexAttribPointer(
		/*attrib index*/0, 
		/*size (count)*/3, 
		/*type*/GL_FLOAT,
		/*normalised*/GL_FALSE, 
		/*stride (bits to move from one value to next)*/6 * sizeof(float), 
		/*ptr*/(void*)0);
	glEnableVertexAttribArray(1);

	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	shader.activate();
	shader.setMat4("transform", trans);

	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100), glm::vec3(0.0f, 0.0f, 1.0f));
		
		shader.activate();
		shader.setMat4("transform", trans);

		//draw shapes
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));

		// swap color buffer used to render this render iteration
		// and output it to screen (double buffer doc page 23)
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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
