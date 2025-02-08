#pragma once
#include "../../Input.h"

namespace Cubes {

	class WindowsInput : public Input
	{
	public:
		bool IsKeyDownImpl(int keycode) override;
		bool IsMouseButtonDownImpl(int keycode) override;

		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};

}
