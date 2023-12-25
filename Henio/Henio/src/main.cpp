#include <iostream>

#include "Logger.h"
#include "Window.h"

int main()
{
	std::unique_ptr<Window> w = std::make_unique<Window>();

	if (!w->Init(640, 480, "Henio Game Engine"))
	{
		Logger::LogError("%s error: Window init error\n",
		__FUNCTION__);
		return -1;
	}
	
	w->MainLoop();
	w->Cleanup();
	
	return 0;
}
