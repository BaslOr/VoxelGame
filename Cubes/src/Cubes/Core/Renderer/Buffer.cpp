#include "cbpch.h"
#include "Buffer.h"
#include "../Utility/Log.h"
#include "../Error/Error.h"
#include "../../Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Cubes {

	Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size)
	{
        try
        {
            return CreateVertexBuffer(data, size);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
	}

    Ref<VertexBuffer> Cubes::VertexBuffer::CreateVertexBuffer(void* data, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            throw NoAPISelectedError();
            break;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(data, size);
            break;
        case RendererAPI::API::Vulkan:
            throw APINotSupportedError("Vulkan");
            break;
        }
    }


    /////////////////////////////////////////////////////////////////////////////
    //////////////////////IndexBuffer////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////


    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t count)
    {
        try
        {
            return CreateIndexBuffer(data, count);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    Ref<IndexBuffer> Cubes::IndexBuffer::CreateIndexBuffer(uint32_t* data, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            throw NoAPISelectedError();
            break;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(data, count);
            break;
        case RendererAPI::API::Vulkan:
            throw APINotSupportedError("Vulkan");
            break;
        }
    }

}
