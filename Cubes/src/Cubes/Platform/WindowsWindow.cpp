#include "cbpch.h"
#include "WindowsWindow.h"
#include "../Utility/Log.h"

#include <GLFW/glfw3.h>

namespace Cubes {

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		_data.Width = props.Width;
		_data.Height = props.Height;
		_data.Title = props.Title;
		

		initGLFW();
		_window = glfwCreateWindow(_data.Width, _data.Height, _data.Title.c_str(), NULL, NULL);
		setupOpenGL();
		glfwSetWindowUserPointer(_window, &_data);
		SetVSync(true);
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glClearColor(.23f, .1f, .5f, 1.f);
		glfwSwapBuffers(_window);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data.VSync = enabled;
	}

	void WindowsWindow::initGLFW()
	{
		if (!GLFW_INITIALIZED) {
			if (!glfwInit()) {
				CB_CORE_ERROR("GLFW isn't initialized");
			}
		}
	}

	void WindowsWindow::setupOpenGL()
	{
		glfwMakeContextCurrent(_window);
	}

}
