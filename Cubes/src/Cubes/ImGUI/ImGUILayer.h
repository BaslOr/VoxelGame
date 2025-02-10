#pragma once
#include "../Platform/OpenGL/ImGUIOpenGLRenderer.h"
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
		void OnEvent(Event& e) override;
		void OnUpdate()  override;

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrollEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);

	private:	
		float _time = 0.f;
	};

}
