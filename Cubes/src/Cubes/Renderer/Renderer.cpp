#include "cbpch.h"
#include "Renderer.h"

#include "Renderer2D.h"


namespace Cubes {

	Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;


	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowsResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		_sceneData->ViewProjectionMatrix = camera.GetViewProjection();
		Renderer2D::BeginScene(camera);

		RenderCommand::SetClearColor(glm::vec4(.23f, .3f, .5f, 1.f));
		RenderCommand::Clear();
	}

	void Renderer::EndScene()
	{
		Renderer2D::EndScene();
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelMatrix)
	{
		vertexArray->Bind();
		shader->SetUniformMat4("u_ViewProjection", _sceneData->ViewProjectionMatrix);
		shader->SetUniformMat4("u_Model", modelMatrix);
		RenderCommand::DrawIndexed(vertexArray);
	}
}