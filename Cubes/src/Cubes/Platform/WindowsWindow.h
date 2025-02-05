#pragma once
#include <GLFW/glfw3.h>
#include "../Utility/Window.h"

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

		inline void SetEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		inline bool IsVSync() override { return _data.VSync; }

	private:

		void initGLFW();
		void setupOpenGL();

		GLFWwindow* _window;

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
