#pragma once
#include "Core.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

namespace Cubes {

	class CB_API Input {
	public: 
		inline static bool IsKeyPressed(int keycode) { return _instance->IsKeyDownImpl(keycode); }

		inline static bool IsMouseButtonDown(int keycode) { return _instance->IsMouseButtonDownImpl(keycode); }
		inline static float GetMouseX() { return _instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return _instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyDownImpl(int keycode) = 0;

		virtual bool IsMouseButtonDownImpl(int keycode) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* _instance;
	};

}