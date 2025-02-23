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
        static void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color);

        

    };

}
