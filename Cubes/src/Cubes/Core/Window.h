#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace Cubes {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;

		WindowProps() {
			Title = "New Window";
			Width = 1280;
			Height = 720;
		}
	};

	class CB_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void* GetNative() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool state) = 0;
		virtual bool IsVSync() = 0;
		virtual void SetInputModeCursor(bool enabled) = 0;
		

		static Window* Create(const WindowProps& props = WindowProps());
	};

}
