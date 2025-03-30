#pragma once 
#include <Cubes.h>

#include "Camera.h"

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
        Camera _camera;

        glm::vec2 _viewPortSize;

        Ref<Texture> _texture;
        Model _model;
    };

}
