#pragma once
#include <GLFW/glfw3.h>

#include "../Core.h"

namespace Cubes {

	class CB_API Window
	{
	public:
		Window(uint32_t width, uint32_t height, std::string title);
		~Window();

		void OnUpdate();

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		inline GLFWwindow* GetWindow() { return _window; }

	private:
		GLFWwindow* _window;

		inline static uint32_t _windowCount = 0;

	};

}
