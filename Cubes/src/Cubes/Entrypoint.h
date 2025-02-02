#include "Application.h"

#ifdef CB_PLATFORM_WINDOWS
	
int main(int argc, char** argv) {
	Cubes::Application* app = Cubes::CreateApplication();
	app->run();
	delete app;
}

#endif // CB_PLATFORM_WINDOWS
