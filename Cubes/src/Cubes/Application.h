#pragma once
#include "Core.h"

namespace Cubes {

    class CB_API Application {
    public:
        Application();
        virtual ~Application();
        virtual void run() = 0;
    };

	//To be defined in Client
	Application* CreateApplication();

}