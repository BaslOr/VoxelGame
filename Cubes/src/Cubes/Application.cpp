#include "cbpch.h"
#include "Application.h"


namespace Cubes{

	Application* Application::_instance = nullptr;

	Application::Application()
	{
		if (_instance != nullptr)
			CB_CORE_ERROR("Application already exists");
		_instance = this;

		Cubes::Log::init();
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(CB_BIND_EVENT_FUNC(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(CB_BIND_EVENT_FUNC(Application::OnWindowClose));

		for (auto it = _layerStack.end(); it != _layerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}


	void Application::run()
	{
		while (_isRunning) {
			//Update
			_window->OnUpdate();

			for (Layer* layer : _layerStack)
				layer->OnUpdate();

			CB_CORE_TRACE(Input::IsKeyDown(GLFW_KEY_N));

		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_isRunning = false;
		return true;
	}

}
