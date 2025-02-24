#pragma once
#include "../Layer.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/KeyEvent.h"

namespace Cubes {

	class CB_API ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		~ImGUILayer();
		
		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:	
		float _time = 0.f;
	};

}
