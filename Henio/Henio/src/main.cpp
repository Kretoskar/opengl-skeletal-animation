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
	
	return 0;
}
