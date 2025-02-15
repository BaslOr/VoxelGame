#pragma once
#include "RendererAPI.h"

namespace Cubes {

	class RendererCommand
	{
	public:
		
		inline static void Clear() { _rendererAPI->Clear(); }
		inline static void SetClearColor(const glm::vec4& color) { _rendererAPI->SetClearColor(color); }

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { _rendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* _rendererAPI;
	};

}
