#pragma once
#include "../Core/Layer.h"
#include "../Core/Events/ApplicationEvent.h"
#include "../Core/Events/MouseEvent.h"
#include "../Core/Events/KeyEvent.h"
#include <imgui.h>

namespace Cubes {

	class CB_API ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		~ImGUILayer();
		
		void OnAttach() override;
		void OnDetach() override;

		void Begin();
		void End();

	private:	
		float _time = 0.f;
	};

}
