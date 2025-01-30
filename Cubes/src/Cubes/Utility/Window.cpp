#include "Window.h"

namespace Cubes {


	Window::Window(int width, int height, std::string title)
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

	int Window::GetWidth() const
	{
		int width;
		glfwGetWindowSize(_window, &width, nullptr);

		return width;
	}

	int Window::GetHeight() const
	{
		int height;
		glfwGetWindowSize(_window, nullptr, &height);

		return height;
	}

}
