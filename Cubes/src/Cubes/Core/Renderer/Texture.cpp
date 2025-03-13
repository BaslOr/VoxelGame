#include "cbpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLTexture2D.h"
#include "../Error/Error.h"

namespace Cubes {


    Ref<Texture> Texture::Create(const std::string& texturePath)
    {
        try
        {
            return CreateTexture(texturePath);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    Ref<Texture> Cubes::Texture::CreateTexture(const std::string& texturePath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            throw NoAPISelectedError();
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(texturePath);
        case RendererAPI::API::Vulkan:
            throw APINotSupportedError("Vulkan");
        }
    }

}
