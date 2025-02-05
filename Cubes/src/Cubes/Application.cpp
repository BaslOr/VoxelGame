#include "cbpch.h"
#include "Application.h"


namespace Cubes{

	Application::Application()
	{
		Cubes::Log::init();
		_window = std::unique_ptr<Window>(Window::Create());
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
