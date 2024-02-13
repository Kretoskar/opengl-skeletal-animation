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

#include <string>

#include "Logger.h"
#include "Window.h"

int main()
{
	
	std::unique_ptr<Window> w = std::make_unique<Window>();
	if (!w->Init(640, 480, "Henio Game Engine"))
	{
		LOG_ERROR("Window init error")
		return -1;
	}
	
	w->MainLoop();
	w->Cleanup();
	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

	Model model(glm::vec3(0, 0, -15), glm::vec3(0.05f));
	model.LoadModel("assets/models/monke/scene.gltf");

	SpotLight spotLight =
		{
			camera.cameraPos, camera.cameraFront, 1.0f, 0.07f, 0.032f,
			glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(20.0f)),
			glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f)
		};

	DirLight dirLight = {glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.1f), glm::vec3(0.4f), glm::vec3(0.5f)};
	
	return 0;
}
