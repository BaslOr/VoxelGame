#pragma once
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "PerspectiveCamera.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"

namespace Cubes {


    using RendererID = uint32_t;


    class Renderer {
    public:

        static void Init();
        static void ShutDown();

        static void OnWindowsResize(uint32_t width, uint32_t height);
        static void EnableWireframeMode(bool enable);

        static void BeginScene(PerspectiveCamera& camera);
        static void EndScene();

        static void DrawModel(Model& model, glm::vec3& position, glm::vec3& size = glm::vec3(1.f), glm::vec4& color = glm::vec4(1.f));
        static void DrawCube(glm::vec3& position, glm::vec3& size = glm::vec3(1.f), glm::vec4& color = glm::vec4(1.f, 0.f, 0.f, 1.f));
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelMatrix = glm::mat4(1.f));

        inline static RendererAPI::API GetAPI() { return  RendererAPI::GetAPI(); }


    private:
        static void InitCubeData();
    };

}