#include "cbpch.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include <GLFW/glfw3.h>


namespace Cubes {

    Application* Application::_instance = nullptr;


    Application::Application()
    {
        if (_instance != nullptr)
            CB_CORE_ERROR("Application already exists");
        _instance = this;

        Cubes::Log::init();

        _window = std::unique_ptr<Window>(Window::Create());
        _window->SetEventCallback(CB_BIND_EVENT_FUNC(Application::OnEvent));

        Renderer::Init();
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(CB_BIND_EVENT_FUNC(Application::OnWindowClose));

        for (auto it = _layerStack.end(); it != _layerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.IsHandled())
                break;
        }

        _camera.OnEvent(event);
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
            float time = (float)glfwGetTime(); //TODO: Platform::GetTime();
            TimeStep deltaTime = time - _lastFrameTime;
            _lastFrameTime = time;

            _window->OnUpdate();

            OnUpdate(deltaTime);

            for (Layer* layer : _layerStack)
                layer->OnUpdate();

        }
    }


    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        _isRunning = false;
        return true;
    }

}
