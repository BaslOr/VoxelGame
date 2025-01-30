#include "Application.h"
#include "Utility/Log.h"
#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

#ifdef CB_PLATFORM_WINDOWS
	
int main(int argc, char** argv) {
	Cubes::Log::init();

	Cubes::Application* app = Cubes::CreateApplication();
	app->run();
	delete app;
}

#endif // CB_PLATFORM_WINDOWS
