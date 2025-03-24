#include "cbpch.h"
#include "Framebuffer.h"

#include "Renderer.h"
#include "../Error/Error.h"
#include "../../Platform/OpenGL/OpenGLFramebuffer.h"


namespace Cubes {

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        try
        {
            return CreateFramebuffer(spec);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    Ref<Framebuffer> Framebuffer::CreateFramebuffer(const FramebufferSpecification& spec)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            throw NoAPISelectedError();
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLFramebuffer>(spec);
        case RendererAPI::API::Vulkan:
            throw APINotSupportedError("Vulkan");
        }
    }

}
