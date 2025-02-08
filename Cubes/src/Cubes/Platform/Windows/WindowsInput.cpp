#include "cbpch.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "../../Application.h"

namespace Cubes {

	Input* Input::_instance = new WindowsInput();

	bool WindowsInput::IsKeyDownImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNative());

		int status = glfwGetKey(window, keycode); // TODO: Add Cubes Keycode
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonDownImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNative());

		int status = glfwGetMouseButton(window, keycode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNative());
		
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return static_cast<float>(x);
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNative());

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return static_cast<float>(y);
	}

}
