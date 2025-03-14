#pragma once
#include "PerspectiveCamera.h"

#include <glm/glm.hpp>
#include "Texture.h"

namespace Cubes {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();
        static void BeginScene();
        static void EndScene();

        //Primitives
        static void DrawQuad(glm::vec3& position, glm::vec2& size = glm::vec2(1.f, 1.f), glm::vec4& color = glm::vec4(1.f, 0.f, 0.f, 1.f), float rotation = 0.f);
        static void DrawQuad(glm::vec2& position, glm::vec2& size = glm::vec2(1.f, 1.f), glm::vec4& color = glm::vec4(1.f, 0.f, 0.f, 1.f), float rotation = 0.f);

        static void DrawTexture(Ref<Texture> texture, glm::vec3& position, glm::vec2& size = glm::vec2(1.f), glm::vec4& color = glm::vec4(1.f), float rotation = 0.f);
        static void DrawTexture(Ref<Texture> texture, glm::vec2& position, glm::vec2& size = glm::vec2(1.f), glm::vec4& color = glm::vec4(1.f), float rotation = 0.f);
        
    private:
        static void InitQuadData();

    };

}
