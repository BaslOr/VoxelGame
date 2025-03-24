#pragma once 
#include <Cubes.h>

#include "Camera.h"

class SandboxLayer : public Cubes::Layer {
public:
    SandboxLayer();
    ~SandboxLayer() = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(Cubes::TimeStep deltaTime) override;
    void OnImGuiRender() override;
    void OnEvent(Cubes::Event& event) override;

private:
    Camera _camera;

    Cubes::Ref<Cubes::Texture> _texture;
    Cubes::Model _model;
};
