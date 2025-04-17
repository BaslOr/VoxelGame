#pragma once 
#include <Cubes.h>
#include "Panels/General/SceneHierarchyPanel.h"
#include "Panels/General/ViewportPanel.h"
#include "Panels/PanelManager.h"

namespace Cubes {

    class EditorLayer : public Layer {
    public:
        EditorLayer() = default;
        ~EditorLayer() = default;

        void OnAttach() override;
        void OnDetach() override;

        void OnUpdate(TimeStep deltaTime) override;
        void OnImGuiRender() override;
        void OnEvent(Event& event) override;

        void OpenPanel(Panel* panel);
        void ClosePanel(Panel* panel);

    private:
        void RenderPanels();
        void UpdatePanels();

    private:
        Ref<Scene> _activeScene = CreateRef<Scene>();

        PanelManager _panelManager;
        ViewportPanel* _viewportPanel;
        InspectorPanel* _inspectorPanel;
        SceneHierarchyPanel* _sceneHierarchyPanel;

        Ref<Texture> _texture;
        Ref<Model> _mesh;
        Entity _spriteEntity;
        Entity _meshEntity;
        Entity _cameraEntity;
    };

}
