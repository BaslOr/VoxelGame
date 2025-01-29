#include "Application.h"
#include "Utility/Log.h"

#ifdef CB_PLATFORM_WINDOWS
	
int main(int argc, char** argv) {
	Cubes::Log::init();


	Cubes::Application* app = Cubes::CreateApplication();
	app->run();
	delete app;
}

#endif // CB_PLATFORM_WINDOWS
