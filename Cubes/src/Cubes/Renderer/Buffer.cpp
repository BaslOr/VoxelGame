#include "cbpch.h"
#include "Buffer.h"
#include "../Utility/Log.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

namespace Cubes {
	VertexBuffer* VertexBuffer::Create(void* data, uint32_t size)
	{
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Vertex Buffer"); return nullptr;
            break;
        case RenderAPI::OpenGL:
            return new OpenGLVertexBuffer(data, size);
            break;
        case RenderAPI::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
	}

    IndexBuffer* IndexBuffer::Create(uint16_t* data, uint16_t count)
    {
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Index Buffer"); return nullptr;
            break;
        case RenderAPI::OpenGL:
            return new OpenGLIndexBuffer(data, count);
            break;
        case RenderAPI::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
    }

}