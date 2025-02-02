#include "cbpch.h"
#include "Application.h"


namespace Cubes{

	Application::Application()
	{
		Cubes::Log::init();
		_window = std::make_unique<Window>(1280, 720, "Bin am kochen");
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		_isRunning = true;
		while (_isRunning) {
			_window->OnUpdate();
		}
	}

}
