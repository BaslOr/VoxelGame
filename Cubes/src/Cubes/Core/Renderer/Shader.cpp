#include "cbpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "../../Platform/OpenGL/OpenGLShader.h"
#include "../Error/Error.h"

namespace Cubes {

    //////////Shader/////////////////////////////////////////////////////////////////
    Ref<Shader> Shader::Create(const std::string& filePath)
    {
        try
        {
            return CreateShader(filePath);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    Ref<Shader> Shader::Create(const std::string& name, std::string& vertexCode, std::string& fragmentCode)
    {
        try
        {
            return CreateShader(name, vertexCode, fragmentCode);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    Ref<Shader> Cubes::Shader::CreateShader(const std::string& filePath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            throw NoAPISelectedError();
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLShader>(filePath);
        case RendererAPI::API::Vulkan:
            throw APINotSupportedError("Vulkan");
        }
    }


    Ref<Shader> Cubes::Shader::CreateShader(const std::string& name, std::string& vertexCode, std::string& fragmentCode)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            throw NoAPISelectedError();
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLShader>(name, vertexCode, fragmentCode);
        case RendererAPI::API::Vulkan:
            throw APINotSupportedError("Vulkan");
        }

        CB_CORE_LOG_ERROR("Unkown Rendering API");
        return nullptr;
    }

    ////////////////////Shader Library///////////////////////////////////////////////
    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        CB_CORE_ASSERT_FALSE(Exists(name), "Shader allready exists");
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
        CB_CORE_ASSERT_TRUE(Exists(name), "Shader doesn't exist");
        return _shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name)
    {
        return _shaders.find(name) != _shaders.end();
    }

}