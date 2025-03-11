#pragma once
#include "Event.h"

#include <sstream>

namespace Cubes {

	class CB_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height);
		inline unsigned int GetWidth() const { return _Width; }
		inline unsigned int GetHeight() const { return _Height; }
		std::string ToString() const override;

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int _Width, _Height;
	};

	class CB_API WindowCloseEvent : public Event
	{
	public:
		inline WindowCloseEvent() {}
		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CB_API AppTickEvent : public Event
	{
	public:
		inline AppTickEvent() {}
		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CB_API AppUpdateEvent : public Event
	{
	public:
		inline AppUpdateEvent() {}
		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class CB_API AppRenderEvent : public Event
	{
	public:
		inline AppRenderEvent() {}
		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}