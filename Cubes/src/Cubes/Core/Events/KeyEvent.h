#pragma once

#include <sstream>

#include "Event.h"

namespace Cubes {

	class CB_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return _KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
			: _KeyCode(keycode) {}
		int _KeyCode;
	};

	class CB_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), _RepeatCode(repeatCount) {}
		inline int GetRepeatCount() const { return _RepeatCode; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _KeyCode << " (" << _RepeatCode << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int _RepeatCode;
	};

	class CB_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	};

	class CB_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	};

}