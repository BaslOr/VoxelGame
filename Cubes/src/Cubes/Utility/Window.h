#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

#include "../Core.h"

namespace Cubes {

	class CB_API Window
	{
	public:
		Window(int width, int height, std::string title);
		~Window();

		int GetWidth() const;
		int GetHeight() const;

		inline GLFWwindow* GetWindow() { return _window; }

	private:
		GLFWwindow* _window;

		inline static uint32_t _windowCount = 0;

	};

}
