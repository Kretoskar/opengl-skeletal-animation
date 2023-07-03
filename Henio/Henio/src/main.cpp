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

	Model model(glm::vec3(0, 0, -5), glm::vec3(0.05f));
	model.LoadModel("assets/models/monke/scene.gltf");

	SpotLight spotLight =
		{
			camera.cameraPos, camera.cameraFront, 1.0f, 0.07f, 0.032f,
			glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(20.0f)),
			glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f)
		};

	DirLight dirLight = {glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.1f), glm::vec3(0.4f), glm::vec3(0.5f)};
	
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
		const double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;
		processInput(deltaTime);

		screen.Update();
		
		shader.Activate();
		shader.Set3Float("viewPos", camera.cameraPos);

		dirLight.Render(shader);
		
		shader.SetInt("nPointLights", 0);
		
		spotLight.position = camera.cameraPos;
		spotLight.direction = camera.cameraFront;
		spotLight.Render(0, shader);
		shader.SetInt("nSpotLights", 1);

		const glm::mat4 view = camera.GetViewMatrix();
		const glm::mat4 projection = glm::perspective(glm::radians(camera.GetFov()), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		std::vector<glm::mat4> transforms;
		model.GetBoneTransforms(transforms);
		for (uint32_t i = 0; i < transforms.size(); i++)
		{
			glUniformMatrix4fv(glGetUniformLocation(shader.id, "bones"), (GLsizei)transforms.size(), GL_FALSE, glm::value_ptr(transforms[0]));
		}
		
		model.Render(shader);
		
		screen.NewFrame();
	}

	model.Cleanup();
	
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
