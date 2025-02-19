#include "cbpch.h"
#include "Renderer.h"


namespace Cubes {

	Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;


	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		_sceneData->ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& modelMatrix)
	{
		vertexArray->Bind();
		shader->SetUniformMat4("u_ViewProjection", _sceneData->ViewProjectionMatrix);
		shader->SetUniformMat4("u_Model", modelMatrix);
		RendererCommand::DrawIndexed(vertexArray);
	}
}