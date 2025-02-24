#include "VoxelGame.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <Cubes/Renderer/Renderer2D.h>


namespace GameNamespace {

    VoxelGame::VoxelGame()
        : _camera(glm::vec3(0.f, 0.f, 3.f), 45.f)
    {
        PushOverlay(new Cubes::ImGUILayer());

        _texture = Cubes::Texture::Create("../VoxelGame/Assets/Textures/TestIcon.png");
    }

    void VoxelGame::OnUpdate(Cubes::TimeStep deltaTime)
    {
        //Update
        _camera.OnUpdate(deltaTime);

        //Render
        Cubes::Renderer::BeginScene(_camera);

        Cubes::Renderer2D::DrawTexture(_texture, glm::vec2(0.f), glm::vec2(1.f), glm::vec4(.3f, .5f, .2f, 1.f));
        Cubes::Renderer2D::DrawQuad(glm::vec2(-1.f, 1.f), glm::vec2(0.5f));
        Cubes::Renderer2D::DrawQuad(glm::vec2(1.f, 1.f), glm::vec2(0.5f), glm::vec4(0.f, 1.f, 0.f, 1.f));

        Cubes::Renderer::EndScene();
    }

}
