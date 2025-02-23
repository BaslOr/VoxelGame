#include "cbpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLShader.h"

namespace Cubes {

    Ref<Shader> Shader::Create(const std::string& filePath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Shader"); return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(filePath);
            break;
        case RendererAPI::API::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
    }

	Ref<Shader> Shader::Create(std::string& vertexCode, std::string& fragmentCode)
	{
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Shader"); return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(vertexCode, fragmentCode);
            break;
        case RendererAPI::API::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
	}

}