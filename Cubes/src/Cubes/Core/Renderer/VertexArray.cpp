#include "cbpch.h"
#include "VertexArray.h"
#include "../Utility/Log.h"
#include "../../Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
#include "../Error/Error.h"

namespace Cubes {

    

    Ref<VertexArray> VertexArray::Create()
    {
        try
        {
            return CreateVertexArray();
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    Ref<VertexArray> Cubes::VertexArray::CreateVertexArray()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            throw NoAPISelectedError();
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        case RendererAPI::API::Vulkan:
            throw APINotSupportedError("Vulkan");
        }
    }

}
