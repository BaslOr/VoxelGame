#include "cbpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLTexture2D.h"

namespace Cubes {


    Ref<Texture> Texture::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                CB_CORE_ASSERT(false, "No Graphics API selected"); return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLTexture2D>(path);
            case RendererAPI::API::Vulkan:
                CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
        }

        CB_CORE_ASSERT(false, "Failed to create Texture2D");
        return nullptr;
    }

}
