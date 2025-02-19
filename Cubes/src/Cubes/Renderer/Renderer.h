#pragma once
#include "RendererCommand.h"
#include "RendererAPI.h"
#include "PerspectiveCamera.h"
#include "Shader.h"

namespace Cubes {


    using RendererID = uint32_t;


    class Renderer {
    public:

        static void BeginScene(PerspectiveCamera& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return  RendererAPI::GetAPI(); }

    private: 
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

    private:
        static SceneData* _sceneData;

    };

}