#include "cbpch.h"
#include "VertexArray.h"
#include "../Utility/Log.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"

namespace Cubes {

    

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Vertex Array"); return nullptr;
            break;
        case RenderAPI::OpenGL:
            return new OpenGLVertexArray();
            break;
        case RenderAPI::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
    }

}
