#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Time/TimeStep.h"

namespace Cubes {

	class CB_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual inline void OnAttach() {}
		virtual inline void OnDetach() {}
		virtual inline void OnImGuiRender() {}
		virtual inline void OnUpdate(TimeStep deltaTime) {}
		virtual inline void OnEvent(Event& e) {}

	private:
		std::string _debugName;
	};

}


