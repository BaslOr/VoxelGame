#pragma once
#include "PerspectiveCamera.h"

#include <glm/glm.hpp>

namespace Cubes {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();
        static void BeginScene(PerspectiveCamera& camera);
        static void EndScene();

        //Primitives
        static void DrawQuad(glm::vec2 position, glm::vec2 size = glm::vec2(1.f, 1.f), glm::vec4 color = glm::vec4(1.f, 0.f, 0.f, 1.f), float rotation = 0.f);

        

    };

}
