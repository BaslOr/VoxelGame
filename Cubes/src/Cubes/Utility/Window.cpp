#include "cbpch.h"
#include "Window.h"

namespace Cubes {


	Window::Window(uint32_t width, uint32_t height, std::string title)
	{
		if(_windowCount == 0)
			glfwInit();

		_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		++_windowCount;
	}

	Window::~Window()
	{
		glfwDestroyWindow(_window);
		--_windowCount;
		if(_windowCount == 0)
			glfwTerminate();
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
	}

	uint32_t Window::GetWidth() const
	{
		int width;
		glfwGetWindowSize(_window, &width, nullptr);

		return width;
	}

	uint32_t Window::GetHeight() const
	{
		int height;
		glfwGetWindowSize(_window, nullptr, &height);

		return height;
	}

}
