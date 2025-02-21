#pragma once
#include "RendererCommand.h"
#include "RendererAPI.h"
#include "PerspectiveCamera.h"
#include "Shader.h"

namespace Cubes {


    using RendererID = uint32_t;


    class Renderer {
    public:

        static void Init();

        static void BeginScene(PerspectiveCamera& camera);
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelMatrix = glm::mat4(1.f));

        inline static RendererAPI::API GetAPI() { return  RendererAPI::GetAPI(); }

    private: 
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

    private:
        static SceneData* _sceneData;

    };

}