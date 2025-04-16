#include "ViewportPanel.h"
#include <imgui.h>
#include <Cubes/Core/Renderer/Renderer.h>

namespace Cubes {

	void ViewportPanel::PushStyleVars()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
	}

	void ViewportPanel::OnImGuiRender()
	{
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		_viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint32_t textureID = Renderer::GetFramebufferColorAttachmentID();
		ImGui::Image((void*)textureID, { _viewportSize.x, _viewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	}

	void ViewportPanel::PopStyleVars()
	{
		ImGui::PopStyleVar();
	}

	void ViewportPanel::OnUpdate()
	{
		HandleRezising();
	}

	void ViewportPanel::HandleRezising()
	{
		if (FramebufferSpecification spec = Renderer::GetFramebufferSpecification();
			_viewportSize.x > 0.0f && _viewportSize.y > 0.0f &&
			(spec.Width != _viewportSize.x || spec.Height != _viewportSize.y)) {

			Renderer::ResizeFramebuffer(_viewportSize.x, _viewportSize.y);

			_context->OnViewportResize((uint32_t)_viewportSize.x, (uint32_t)_viewportSize.y);
		}
	}

}
