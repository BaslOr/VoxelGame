#pragma once 
#include <Cubes.h>

#include "Camera.h"

namespace Cubes {

    class EditorLayer : public Layer {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        void OnAttach() override;
        void OnDetach() override;

        void OnUpdate(Cubes::TimeStep deltaTime) override;
        void OnImGuiRender() override;
        void OnEvent(Cubes::Event& event) override;

    private:
        Camera _camera;

        Ref<Texture> _texture;
        Model _model;
    };

}
