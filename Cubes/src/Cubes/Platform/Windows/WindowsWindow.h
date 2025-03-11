#pragma once
#include <GLFW/glfw3.h>
#include "../../Core/Window.h"
#include "../../Core/Renderer/RenderContext.h"

namespace Cubes {

	static bool GLFW_INITIALIZED = false;

	class CB_API WindowsWindow : public Window	
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();

		void OnUpdate() override;

		inline uint32_t GetWidth() const override { return _data.Width; }
		inline uint32_t GetHeight() const override { return _data.Height; }

		inline void* GetNative() const override { return _window; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		inline bool IsVSync() override { return _data.VSync; }

		inline void SetInputModeCursor(bool enabled) override { enabled ? glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) : glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }

	private:

		void initGLFW();
		void setupOpenGL();

		GLFWwindow* _window;
		RenderContext* _context;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData _data;
	};

}
