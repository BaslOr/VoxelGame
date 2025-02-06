#pragma once
#include "Core.h"
#include "Utility/Log.h"
#include "Utility/Window.h"
#include "Events/ApplicationEvent.h"


namespace Cubes {

    class CB_API Application {
    public:
        Application();
        virtual ~Application();
        
        void run();

        void OnEvent(Event& e);
    private:
        
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> _window;

        bool _isRunning;

    };

	//To be defined in Client
	Application* CreateApplication();

}