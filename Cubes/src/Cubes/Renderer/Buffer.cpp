#include "cbpch.h"
#include "Buffer.h"
#include "../Utility/Log.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Cubes {
	VertexBuffer* VertexBuffer::Create(void* data, uint32_t size)
	{
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Vertex Buffer"); return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(data, size);
            break;
        case RendererAPI::API::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
	}

    IndexBuffer* IndexBuffer::Create(uint16_t* data, uint16_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Index Buffer"); return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(data, count);
            break;
        case RendererAPI::API::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
    }

}