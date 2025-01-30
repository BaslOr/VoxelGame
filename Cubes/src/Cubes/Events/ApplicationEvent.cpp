#include "ApplicationEvent.h"

namespace Cubes {

	WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height)
		: _Width(width), _Height(height) {}

	std::string Cubes::WindowResizeEvent::ToString() const
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << _Width << ", " << _Height;
		return ss.str();
	}
}
