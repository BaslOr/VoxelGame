#pragma once
#include "../Panel.h" 

#include <glm/glm.hpp>
#include <Cubes/Core/Project/Scene.h>

namespace Cubes {

	class ViewportPanel : public Panel {
	public:
		ViewportPanel(Scene* context) 
			: Panel("Viewport"), _context(context) { }
		
		void PushStyleVars() override;
		void OnImGuiRender() override;
		void PopStyleVars() override;

		void OnUpdate() override;

		inline void SetContext(Scene* scene) { _context = scene; }

	private:
		void HandleRezising();

	private:
		Scene* _context = nullptr;

		glm::vec2 _viewportSize = {};
	};

}
