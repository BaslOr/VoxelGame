#pragma once
#include "RendererCommand.h"
#include "RendererAPI.h"

namespace Cubes {


    using RendererID = uint32_t;


    class Renderer {
    public:

        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return  RendererAPI::GetAPI(); }

    };

}