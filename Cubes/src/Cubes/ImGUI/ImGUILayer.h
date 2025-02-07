#pragma once
#include "../Platform/OpenGL/ImGUIOpenGLRenderer.h"
#include "../Layer.h"

namespace Cubes {

	class CB_API ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		~ImGUILayer();
		
		void OnAttach() override;
		void OnEvent(Event& e) override;
		void OnUpdate()  override;

	private:	
		float _time = 0.f;
	};

}
