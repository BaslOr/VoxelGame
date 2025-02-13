#include "cbpch.h"
#include "Shader.h"
#include "../Platform/OpenGL/OpenGLShader.h"

namespace Cubes {

	Shader* Shader::Create(std::string vertexCode, std::string fragmentCode)
	{
        switch (Renderer::GetRenderAPI())
        {
        case RenderAPI::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Shader"); return nullptr;
            break;
        case RenderAPI::OpenGL:
            return new OpenGLShader(vertexCode, fragmentCode);
            break;
        case RenderAPI::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
	}

}