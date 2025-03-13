#pragma once
#include "Application.h"
#include "Error/Error.h"
#include "Core.h"

#ifdef CB_PLATFORM_WINDOWS
	
int main(int argc, char** argv) {
	try
	{
		Cubes::Application* app = Cubes::CreateApplication();
		app->run();
		delete app;
	}
	catch (const Cubes::Error& error)
	{
		CB_CORE_LOG_ERROR("An fatal or unhandled error has occured: ");
		CB_CORE_LOG_ERROR("{0}", error.what());
	}
}

#endif // CB_PLATFORM_WINDOWS
