#pragma once
#include "../Utility/Log.h"
#include "../Core.h"
#include "../Error/Error.h"
#include <glm/glm.hpp>

namespace Cubes {

    class VertexShaderCompilationsError : public Error {
    public:
        VertexShaderCompilationsError(const char* errorMessage)
            : Error(errorMessage)
        { }
    };

    class FragmentShaderCompilationsError : public Error {
    public:
        FragmentShaderCompilationsError(const char* errorMessage)
            : Error(errorMessage)
        { }
    };

    class UnkownShaderTypeError : public Error {
    public:
        UnkownShaderTypeError(const char* typeName)
            : Error(std::string(typeName) + " is wrong written or not available in Cubes")
        { }
    };

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual const std::string& GetName() const = 0;

        virtual void SetUniformMat4(std::string name, glm::mat4 matrix) const = 0;
        virtual void SetUniformInt(std::string name, int value) const = 0;
        virtual void SetUniformFloat3(std::string name, glm::vec3 value) const = 0;
        virtual void SetUniformFloat4(std::string name, glm::vec4 value) const = 0;

        static Ref<Shader> Create(const std::string& name, std::string& vertexCode, std::string& fragmentCode);
        static Ref<Shader> Create(const std::string& filePath);

    private:

        static Ref<Shader> CreateShader(const std::string& name, std::string& vertexCode, std::string& fragmentCode);
        static Ref<Shader> CreateShader(const std::string& filePath);
    };


    class ShaderLibrary {
    public:
        static void Add(const Ref<Shader>& shader);
        static void Add(const std::string& name, const Ref<Shader>& shader);
        static Ref<Shader> Load(const std::string& filePath);
        static Ref<Shader> Load(const std::string& name, const std::string& filePath);

        static Ref<Shader> Get(const std::string& name);
    private:
        static bool Exists(const std::string& name);

    private:
        inline static std::unordered_map<std::string, Ref<Shader>> _shaders;

    };

}