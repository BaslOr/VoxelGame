#include "cbpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLShader.h"

namespace Cubes {

    //////////Shader/////////////////////////////////////////////////////////////////
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

    Ref<Shader> Shader::Create(const std::string& name, std::string& vertexCode, std::string& fragmentCode)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            CB_CORE_ERROR("You need to select an Rendering API before creating a Shader"); return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(name, vertexCode, fragmentCode);
            break;
        case RendererAPI::API::Vulkan:
            CB_CORE_ERROR("Vulkan is not supported yet"); return nullptr;
            break;
        }

        CB_CORE_ERROR("Unkown Rendering API");
        return nullptr;
    }


    ////////////////////Shader Library///////////////////////////////////////////////
    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        CB_CORE_ASSERT(!Exists(name), "Shader allready exists");
        _shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        CB_CORE_ASSERT(Exists(name), "Shader allready exists");
        return _shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name)
    {
        return _shaders.find(name) != _shaders.end();
    }

}