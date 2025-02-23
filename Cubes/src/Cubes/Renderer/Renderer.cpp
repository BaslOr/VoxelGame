#include "cbpch.h"
#include "Renderer.h"


namespace Cubes {

	Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;


	void Renderer::Init()
	{
		RendererCommand::Init();
	}

	void Renderer::OnWindowsResize(uint32_t width, uint32_t height)
	{
		RendererCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		_sceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelMatrix)
	{
		vertexArray->Bind();
		shader->SetUniformMat4("u_ViewProjection", _sceneData->ViewProjectionMatrix);
		shader->SetUniformMat4("u_Model", modelMatrix);
		RendererCommand::DrawIndexed(vertexArray);
	}
}