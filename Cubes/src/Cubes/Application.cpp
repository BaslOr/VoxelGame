#include "cbpch.h"
#include "Application.h"


namespace Cubes{

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		Cubes::Log::init();
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		CB_CORE_INFO("{0}", e.ToString());

		
	}


	void Application::run()
	{
		_isRunning = true;
		while (_isRunning) {
			_window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_isRunning = false;
		return true;
	}

}
