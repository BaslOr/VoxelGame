#include "EditorLayer.h"
#include <Cubes/Core/Debug/ScopeTimer.h>

namespace Cubes {

    void EditorLayer::OnAttach()
    {
        _camera = Camera(glm::vec3(0.f, 0.f, 3.f), 45.f);

        _texture = Texture::Create("../Sandbox/Assets/Textures/TestIcon.png");
        _model = ModelLoader::LoadModel("../Sandbox/Assets/3D Models/Dummy.obj", "../Sandbox/Assets/3D Models/Dummy.png");

        _viewPortSize = { 1280, 720 };
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(TimeStep deltaTime)
    {
        static bool wireframeModeEnable = false;
        if (Input::IsKeyDown(CB_KEY_F)) {
            Renderer::EnableWireframeMode(wireframeModeEnable);
            wireframeModeEnable = !wireframeModeEnable;
        }

        //Update
        _camera.OnUpdate(deltaTime);

        //Render
        Renderer::BeginScene(_camera);
    
        Renderer::DrawModel(_model, glm::vec3(1.f, 0.f, 0.f), glm::vec3(1.f));

        Renderer2D::DrawTexture(_texture, glm::vec3(0.f, -1.f, 0.f), glm::vec2(1.f));

        for (uint32_t i = 0; i < 20; i++)
        {
            for (uint32_t j = 0; j < 20; j++)
            {
                glm::vec3 postion(i, -2, j);
                Cubes::Renderer::DrawCube(postion, glm::vec3(1.f), glm::vec4(0.1, 0.6f, 0.2f, 1.f));
            }
        }

        Renderer::EndScene();
    }

    void EditorLayer::OnImGuiRender()
    {
        ScopeTimer scopeTimer("OnImGuiRender");

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");

        ImVec2 currentViewportSize = ImGui::GetContentRegionAvail();
        if (currentViewportSize.x != _viewPortSize.x || currentViewportSize.y != _viewPortSize.y) {
            _viewPortSize.x = currentViewportSize.x;
            _viewPortSize.y = currentViewportSize.y;
            
            FramebufferSpecification spec{};
            spec.Width = static_cast<uint32_t>(_viewPortSize.x);
            spec.Height = static_cast<uint32_t>(_viewPortSize.y);
            Renderer::RecreateFramebuffer(spec);
        }

        uint32_t textureID = Cubes::Renderer::GetFramebufferColorAttachmentID();
        ImGui::Image((void*)textureID, { _viewPortSize.x, _viewPortSize.y }, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Stats");

        ImGui::Text("Some kind of statistics: ");

        ImGui::End();
    }

    void EditorLayer::OnEvent(Cubes::Event& event)
    {
    }

}
