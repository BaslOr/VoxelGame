#pragma once
#include "RendererAPI.h"

namespace Cubes {

	class RenderCommand
	{
	public:
		inline static void Init() { _rendererAPI->Init(); }

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { _rendererAPI->SetViewport(x, y, width, height); }

		inline static void EnableWireframeMode(bool enable) { _rendererAPI->EnableWireframeMode(enable); }
		
		inline static void Clear() { _rendererAPI->Clear(); }
		inline static void SetClearColor(const glm::vec4& color) { _rendererAPI->SetClearColor(color); }

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { _rendererAPI->DrawIndexed(vertexArray); }


	private:
		static RendererAPI* _rendererAPI;
	};

}
