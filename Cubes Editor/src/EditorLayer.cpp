#include "EditorLayer.h"
#include <Cubes/Core/Debug/ScopeTimer.h>
#include <glm/gtc/matrix_transform.hpp>


namespace Cubes {

    void EditorLayer::OnAttach()
    {

        _texture = Texture::Create("../Sandbox/Assets/Textures/TestIcon.png");
        _mesh = std::make_shared<Model>(ModelLoader::LoadModel("../Sandbox/Assets/3D Models/Dummy.obj", "../Sandbox/Assets/3D Models/Dummy.png"));

        _viewPortSize = { 1280, 720 };


        _spriteEntity = _activeScene->CreateEntity();
        _spriteEntity.AddComponent<SpriteRendererComponent>();
        auto& spriteComponent = _spriteEntity.GetComponent<SpriteRendererComponent>();
        spriteComponent.Color = glm::vec4(1.f);
        spriteComponent.Sprite = _texture;

        _meshEntity = _activeScene->CreateEntity();
        _meshEntity.AddComponent<MeshRendererComponent>();
        auto& meshComponent = _meshEntity.GetComponent<MeshRendererComponent>();
        meshComponent.Color = glm::vec4(1.f);
        meshComponent.Mesh = _mesh;
        auto& transformComponent = _meshEntity.GetComponent<TransformComponent>();
        transformComponent.Transform = glm::translate(glm::mat4(1.f), { -1.f, 0.f, 0.f });

        _cameraEntity = _activeScene->CreateEntity();
        auto& cameraComponent = _cameraEntity.AddComponent<CameraComponent>();
        auto& cameraTransform = _cameraEntity.GetComponent<TransformComponent>();
        cameraTransform.Transform = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 3.f));

        class CameraController : public ScriptableEntity 
        {
        public:
            void OnCreate()
            {
                
            }

            void OnDestroy()
            {

            }

            void OnUpdate(TimeStep deltaTime)
            {
                auto& transform = GetComponent<TransformComponent>().Transform;
                
                if (Input::IsKeyPressed(CB_KEY_W))
                    transform[3][2] -= _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_S))
                    transform[3][2] += _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_A))
                    transform[3][0] -= _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_D))
                    transform[3][0] += _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_SPACE))
                    transform[3][1] += _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_LEFT_SHIFT))
                    transform[3][1] -= _cameraSpeed * deltaTime;
            }

        private:
            float _cameraSpeed = 2.5;
        };
        _cameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
    }

    void EditorLayer::OnDetach()
    {
    }

    void EditorLayer::OnUpdate(TimeStep deltaTime)
    {
        static bool wireframeModeEnable = false;
        if (Input::IsKeyPressed(CB_KEY_F)) {
            Renderer::EnableWireframeMode(wireframeModeEnable);
            wireframeModeEnable = !wireframeModeEnable;
        }

        //Resize
        if (FramebufferSpecification spec = Renderer::GetFramebufferSpecification();
            _viewPortSize.x > 0.0f && _viewPortSize.y > 0.0f && 
            (spec.Width != _viewPortSize.x || spec.Height != _viewPortSize.y)) {

            Renderer::ResizeFramebuffer(_viewPortSize.x, _viewPortSize.y);

            _activeScene->OnViewportResize((uint32_t)_viewPortSize.x, (uint32_t)_viewPortSize.y);
        }

        //Update
        _activeScene->Update(deltaTime);
    }

    void EditorLayer::OnImGuiRender()
    {
        ScopeTimer scopeTimer("OnImGuiRender");

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        _viewPortSize = { viewportPanelSize.x, viewportPanelSize.y };

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
