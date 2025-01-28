#pragma once
#include "Core.h"

namespace Cubes {

	class CB_API Application
	{
	public:   
		Application() = default;
		virtual ~Application() = default;

		virtual void run() = 0;

	private:

	};

	//To be defined in Client
	Application* CreateApplication();

}