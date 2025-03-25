#include "SandboxLayer.h"


SandboxLayer::SandboxLayer()
{

}

void SandboxLayer::OnAttach()
{
	_camera = Camera(glm::vec3(0.f, 0.f, 3.f), 45.f);

	_texture = Cubes::Texture::Create("../Sandbox/Assets/Textures/TestIcon.png");
	_model = Cubes::ModelLoader::LoadModel("../Sandbox/Assets/3D Models/Dummy.obj", "../Sandbox/Assets/3D Models/Dummy.png");
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(Cubes::TimeStep deltaTime)
{
	static bool wireframeModeEnable = false;
	if (Cubes::Input::IsKeyDown(CB_KEY_F)) {
		Cubes::Renderer::EnableWireframeMode(wireframeModeEnable);
		wireframeModeEnable = !wireframeModeEnable;
	}

	//Update
	_camera.OnUpdate(deltaTime);

	//Render
	Cubes::Renderer::BeginScene(_camera);

	Cubes::Renderer::DrawModel(_model, glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f));

	Cubes::Renderer2D::DrawTexture(_texture, glm::vec3(0.f, -1.f, 0.f), glm::vec2(1.f));

	for (uint32_t i = 0; i < 20; i++)
	{
		for (uint32_t j = 0; j < 20; j++)
		{
			glm::vec3 postion(i, -2, j);
			Cubes::Renderer::DrawCube(postion, glm::vec3(1.f), glm::vec4(0.1, 0.6f, 0.2f, 1.f));
		}
	}

	Cubes::Renderer::EndScene();
}

void SandboxLayer::OnImGuiRender()
{
	ImGui::Begin("Viewport");

	uint32_t textureID = Cubes::Renderer::GetFramebufferColorAttachmentID();
	ImGui::Image((void*)textureID, ImVec2(1280, 720), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}

void SandboxLayer::OnEvent(Cubes::Event& event)
{
}
