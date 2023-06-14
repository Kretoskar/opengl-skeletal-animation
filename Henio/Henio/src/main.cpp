#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// glm test
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);


	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	std::cout << vec.x << vec.y << vec.z << std::endl;


	glfwInit();

	// using 3.3 as it's the doc supported version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const uint16_t windowWidth = 800;
	const uint16_t windowHeight = 600;

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

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// swap color buffer used to render this render iteration
		// and output it to screen (double buffer doc page 23)
		glfwSwapBuffers(window);
		// checks for events and updates window state
		glfwPollEvents();
	}


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