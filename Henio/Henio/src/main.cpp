#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
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