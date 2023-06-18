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
#include "Components/Public/Camera.h"
#include "Output/Public/Screen.h"
#include "Rendering/Public/Texture.h"
#include "Rendering/Models/Public/Cube.hpp"
#include "Rendering/Models/Public/Lamp.hpp"

void processInput(double deltaTime);

Gamepad mainGamepad(0);

uint16_t SCR_WIDTH = 800;
uint16_t SCR_HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Screen screen;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	glfwInit();
	
	// using 3.3 as it's the doc supported version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!screen.Init())
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// init GLAD
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	screen.SetParameters();
	
	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");
	Shader lampShader("assets/vertex_core.glsl", "assets/lamp.glsl");

	Cube cube(Material::emerald, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.75f));
	cube.Init();

	Lamp lamp(glm::vec3(-1.0f, -0.5f, -0.5f), glm::vec3(0.25f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
	lamp.Init();
	
	mainGamepad.Update();
	if (mainGamepad.IsPresent())
	{
		std::cout << mainGamepad.GetName() << " is present." << std::endl;
	}
	else
	{
		std::cout << "Gamepad not present" << std::endl;
	}
	
	while (!screen.ShouldClose())
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		
		processInput(deltaTime);

		screen.Update();
		
		shader.Activate();
		shader.Set3Float("light.position", lamp.pos);
		shader.Set3Float("viewPos", camera.cameraPos);

		shader.Set3Float("light.ambient", lamp.ambient);
		shader.Set3Float("light.diffuse", lamp.diffuse);
		shader.Set3Float("light.specular", lamp.specular);
		
		// create transformation for screen
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.GetFov()), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		cube.Render(shader);

		lampShader.Activate();
		lampShader.SetMat4("view", view);
		lampShader.SetMat4("projection", projection);
		lamp.Render(lampShader);
		
		screen.NewFrame();
	}

	cube.Cleanup();
	lamp.Cleanup();
	
	glfwTerminate();
	return 0;
}

void processInput(double deltaTime)
{
	if (Keyboard::Key(GLFW_KEY_ESCAPE))
	{
		screen.SetShouldClose(true);
	}

	// move camera
	if (Keyboard::Key(GLFW_KEY_W))
	{
		camera.UpdateCameraPosition(CameraDirection::FORWARD, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_S))
	{
		camera.UpdateCameraPosition(CameraDirection::BACKWARD, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_A))
	{
		camera.UpdateCameraPosition(CameraDirection::LEFT, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_D))
	{
		camera.UpdateCameraPosition(CameraDirection::RIGHT, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_SPACE))
	{
		camera.UpdateCameraPosition(CameraDirection::UP, deltaTime);
	}

	if (Keyboard::Key(GLFW_KEY_LEFT_SHIFT))
	{
		camera.UpdateCameraPosition(CameraDirection::DOWN, deltaTime);
	}

	double dx = Mouse::GetMouseDeltaX() / 50;
	double dy = Mouse::GetMouseDeltaY() / 50;

	if (glm::abs(dx) > glm::epsilon<double>() || glm::abs(dy) > glm::epsilon<double>())
	{
		camera.UpdateCameraDirection(dx, dy);
	}

	double scrollDy = Mouse::GetScrollDeltaY();
	if (glm::abs(scrollDy) > glm::epsilon<double>())
	{
		camera.UpdateCameraFov(scrollDy);
	}
}
