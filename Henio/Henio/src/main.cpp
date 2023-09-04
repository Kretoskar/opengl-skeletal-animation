#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include "Rendering/Public/Shader.h"
#include "Input/Public/Keyboard.h"
#include "Input/Public/Mouse.h"
#include "Input/Public/Gamepad.h"
#include "Components/Public/Camera.h"
#include "Components/Public/CameraComponent.h"
#include "Components/Public/TransformComponent.h"
#include "Core/ECS/Public/Coordinator.h"
#include "Output/Public/HenioCore.h"
#include "Rendering/Public/Texture.h"
#include "Rendering/Models/Public/Cube.hpp"
#include "Rendering/Models/Public/Lamp.hpp"
#include "Systems/CameraSystem.h"
#include "Systems/InputSystem.h"

Gamepad mainGamepad(0);

uint16_t SCR_WIDTH = 800;
uint16_t SCR_HEIGHT = 600;

HenioCore henioCore;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

ECS::Coordinator coordinator;

int main()
{
	henioCore.Init();
	coordinator.Init();
	
	coordinator.RegisterComponent<TransformComponent>();
	coordinator.RegisterComponent<InputComponent>();
	coordinator.RegisterComponent<CameraComponent>();
	
	std::shared_ptr<CameraSystem> cameraSystem = coordinator.RegisterSystem<CameraSystem>();
	ECS::Signature cameraSystemSignature;
	cameraSystemSignature.set(coordinator.GetComponentType<TransformComponent>());
	cameraSystemSignature.set(coordinator.GetComponentType<InputComponent>());
	cameraSystemSignature.set(coordinator.GetComponentType<CameraComponent>());
	coordinator.SetSystemSignature<CameraSystem>(cameraSystemSignature);

	std::shared_ptr<InputSystem> inputSystem = coordinator.RegisterSystem<InputSystem>();
	ECS::Signature inputSystemSignature;
	inputSystemSignature.set(coordinator.GetComponentType<InputComponent>());
	coordinator.SetSystemSignature<InputSystem>(inputSystemSignature);

	std::vector<ECS::Entity> entities = std::vector<ECS::Entity>();

	ECS::Entity cameraEntity = ECS::Entity();
	coordinator.AddComponent(cameraEntity, TransformComponent());
	coordinator.AddComponent(cameraEntity, InputComponent());
	coordinator.AddComponent(cameraEntity, CameraComponent());
	
	entities.emplace_back(cameraEntity);

	long long startTime = GetTickCount();
	
	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

	Model model(glm::vec3(0, 0, -5), glm::vec3(0.05f));
	model.LoadModel("assets/models/monke/scene.gltf");

	DirLight dirLight = {glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.1f), glm::vec3(0.4f), glm::vec3(0.5f)};

	long long startTimeMillis = GetTickCount();

	cameraSystem->Init();
	
	while (!henioCore.ShouldClose())
	{
		const double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		long long currentTimeMillis = GetTickCount();
		//TODO: change to currenttime?
		float animTimeSec = static_cast<float>(currentTimeMillis - startTimeMillis) / 1000.0f;
		
		henioCore.Update();
		inputSystem->Update(deltaTime);
		cameraSystem->Update(deltaTime);
		
		shader.Activate();
		shader.Set3Float("viewPos", cameraSystem->CamTransformComp.position);

		dirLight.Render(shader);
		
		shader.SetInt("nPointLights", 0);
		shader.SetInt("nSpotLights", 0);

		const glm::mat4 view = cameraSystem->CamTransformComp.GetViewMatrix();
		const glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		std::vector<glm::mat4> transforms;
		
		model.GetBoneTransforms(animTimeSec, transforms);
		
		for (uint32_t i = 0; i < transforms.size(); i++)
		{
			glUniformMatrix4fv(glGetUniformLocation(shader.id, "bones"), (GLsizei)transforms.size(), GL_FALSE, glm::value_ptr(transforms[0]));
		}
		
		model.Render(shader);
		
		henioCore.NewFrame();
	}

	model.Cleanup();
	
	glfwTerminate();
	return 0;
}