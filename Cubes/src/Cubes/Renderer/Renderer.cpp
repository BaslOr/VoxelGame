#include "cbpch.h"
#include "Renderer.h"


namespace Cubes {

	Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;


	void Renderer::BeginScene(OrthograpicCamera& camera)
	{
		_sceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		shader->Bind();
		shader->SetUniformMat4("u_ViewProjection", _sceneData->ViewProjectionMatrix);
		RendererCommand::DrawIndexed(vertexArray);
	}
}