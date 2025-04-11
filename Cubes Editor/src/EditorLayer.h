#pragma once 
#include <Cubes.h>
#include "Panels/SceneHierarchyPanel.h"

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

    private:
        Ref<Scene> _activeScene = std::make_shared<Scene>();
        Entity _spriteEntity;
        Entity _meshEntity;
        Entity _cameraEntity;

        Ref<SceneHierarchyPanel> _sceneHierarchy = std::make_shared<SceneHierarchyPanel>(_activeScene.get());

        glm::vec2 _viewPortSize;

        Ref<Texture> _texture;
        Ref<Model> _mesh;
    };

}
