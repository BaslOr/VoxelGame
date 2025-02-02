#pragma once
#include "Core.h"
#include "Utility/Log.h"
#include "Utility/Window.h"


namespace Cubes {

    class CB_API Application {
    public:
        Application();
        virtual ~Application();
        virtual void run();

    private:
        std::unique_ptr<Window> _window;

        bool _isRunning;
    };

	//To be defined in Client
	Application* CreateApplication();

}