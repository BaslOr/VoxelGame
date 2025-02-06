#pragma once
#include "Core.h"
#include "Utility/Log.h"
#include "Utility/Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"


namespace Cubes {

    class CB_API Application {
    public:
        Application();
        virtual ~Application();
        
        void run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

    private:
        
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> _window;
        LayerStack _layerStack;

        bool _isRunning = true;

    };

	//To be defined in Client
	Application* CreateApplication();

}