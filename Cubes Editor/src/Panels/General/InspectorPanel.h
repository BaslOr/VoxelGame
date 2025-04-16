#pragma once 
#include "../Panel.h"
#include <Cubes/Core/Project/Entity.h>

namespace Cubes {

	class InspectorPanel : public Panel {
	public:
		InspectorPanel();

		void OnImGuiRender() override;

		inline Entity GetSelectedEntity() const { return _selectedEntity; }
		inline void SetSelectedEntity(Entity entity) { _selectedEntity = entity; }

	private:
		void DrawComponents();
		void DrawAddComponentButton();

	private:
		Entity _selectedEntity;
	};

}
