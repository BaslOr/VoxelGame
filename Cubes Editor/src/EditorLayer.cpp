#include "EditorLayer.h"
#include <Cubes/Core/Debug/ScopeTimer.h>
#include <glm/gtc/matrix_transform.hpp>


namespace Cubes {

    void EditorLayer::OnAttach()
    {

        _texture = Texture::Create("../Sandbox/Assets/Textures/TestIcon.png");
        _mesh = std::make_shared<Model>(ModelLoader::LoadModel("../Sandbox/Assets/3D Models/Dummy.obj", "../Sandbox/Assets/3D Models/Dummy.png"));

        _spriteEntity = _activeScene->CreateEmptyEntity("Grass Sprite");
        _spriteEntity.AddComponent<SpriteRendererComponent>();
        auto& spriteComponent = _spriteEntity.GetComponent<SpriteRendererComponent>();
        spriteComponent.Color = glm::vec4(1.f);
        spriteComponent.Sprite = _texture;

        _meshEntity = _activeScene->CreateEmptyEntity("Player");
        _meshEntity.AddComponent<MeshRendererComponent>();
        auto& meshComponent = _meshEntity.GetComponent<MeshRendererComponent>();
        meshComponent.Color = glm::vec4(1.f);
        meshComponent.Mesh = _mesh;
        auto& transformComponent = _meshEntity.GetComponent<TransformComponent>();
        transformComponent.Position = { -1.f, 0.f, 0.f };

        _cameraEntity = _activeScene->CreateEmptyEntity("Camera");
        auto& cameraComponent = _cameraEntity.AddComponent<CameraComponent>();
        auto& cameraTransform = _cameraEntity.GetComponent<TransformComponent>();
        cameraTransform.Position = { 0.f, 0.f, 3.f };

        class CameraController : public ScriptableEntity 
        {
        public:
            void OnCreate()
            {
                auto& position = GetComponent<TransformComponent>().Position;
                position.x = 0;
            }

            void OnDestroy()
            {

            }

            void OnUpdate(TimeStep deltaTime)
            {
                auto& position = GetComponent<TransformComponent>().Position;
                
                if (Input::IsKeyPressed(CB_KEY_W))
                    position.z -= _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_S))
                    position.z += _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_A))
                    position.x -= _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_D))
                    position.x += _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_SPACE))
                    position.y += _cameraSpeed * deltaTime;
                if (Input::IsKeyPressed(CB_KEY_LEFT_SHIFT))
                    position.y -= _cameraSpeed * deltaTime;
            }

        private:
            float _cameraSpeed = 2.5;
        };
        _cameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();

        //Open Default Panels
        _inspectorPanel = new InspectorPanel();
        _sceneHierarchyPanel = new SceneHierarchyPanel(_activeScene.get(), _inspectorPanel);
        _viewportPanel = new ViewportPanel(_activeScene.get());
        OpenPanel(_viewportPanel);
        OpenPanel(_inspectorPanel);
        OpenPanel(_sceneHierarchyPanel);
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

        //Update
        UpdatePanels();
        _activeScene->Update(deltaTime);
    }

    void EditorLayer::OnImGuiRender()
    {
        ScopeTimer scopeTimer("OnImGuiRender");

        RenderPanels();
    }

    void EditorLayer::OnEvent(Cubes::Event& event)
    {
    }

    void EditorLayer::OpenPanel(Panel* panel)
    {
        _panelManager.OpenPanel(panel);
        panel->OnAttach();
    }

    void EditorLayer::ClosePanel(Panel* panel)
    {
        panel->OnDetach();
        _panelManager.ClosePanel(panel);
    }

    void EditorLayer::RenderPanels()
    {
        for (auto* panel : _panelManager) {
            panel->PushStyleVars();
            ImGui::Begin(panel->GetName().c_str());
            panel->OnImGuiRender();
            ImGui::End();
            panel->PopStyleVars();
        }
    }

    void EditorLayer::UpdatePanels()
    {
        for (auto* panel : _panelManager) {
            panel->OnUpdate();
        }
    }

}
