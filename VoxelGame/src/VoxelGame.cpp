#include "VoxelGame.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <Cubes/Core/Renderer/Renderer2D.h>


namespace GameNamespace {

    VoxelGame::VoxelGame()
        : _camera(glm::vec3(0.f, 0.f, 3.f), 45.f)
    {
        //_texture = Cubes::Texture::Create("../VoxelGame/Assets/Textures/TestIcon.png");
    }

    void VoxelGame::OnUpdate(Cubes::TimeStep deltaTime)
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

        // Z etwas zurück, Shader mit fester Farbe testen:
        Cubes::Renderer2D::DrawQuad(glm::vec3(0.f, 0.f, -1.f));


        for (uint32_t i = 0; i < 20; i++)
        {
            for (uint32_t j =  0; j < 20; j++)
            {
                glm::vec3 postion(i, -1, j);
                Cubes::Renderer::DrawCube(postion, glm::vec3(1.f), glm::vec4(0.5f, 0.5f, 0.5f, 1.f));
            }
        }

        Cubes::Renderer::EndScene();
    }

}
