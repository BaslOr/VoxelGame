#include "cbpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "../../Core/Core.h"
#include "../../Core/Renderer/Shader.h"


namespace Cubes {

    class ProgramLinkingError : public Error {
    public:
        ProgramLinkingError(const char* errorMessage)
            : Error(errorMessage)
        { }
    };

    static uint32_t ShaderTypeFromString(const std::string& type) {

        try
        {
            if (type == "vertex")
                return GL_VERTEX_SHADER;
            if (type == "fragment")
                return GL_FRAGMENT_SHADER;
            if (type == "pixel")
                return GL_FRAGMENT_SHADER;

            throw UnkownShaderTypeError(type.c_str());
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }


    OpenGLShader::OpenGLShader(const std::string& filePath)
    {
        std::string source = ReadShaderFile(filePath);
        auto shaderSources = ProcessShaderFile(source);
        Compile(shaderSources);

        //Extract name from filePath
        auto lastSlash = filePath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filePath.rfind('.');
        auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
        _name = filePath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string& name, std::string& vertexCode, std::string& fragmentCode)
        : _name(name)
    {
        std::unordered_map<uint32_t, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexCode;
        sources[GL_FRAGMENT_SHADER] = vertexCode;
        Compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(_rendererID);
    }

    void OpenGLShader::Compile(std::unordered_map<uint32_t, std::string>& sources)
    {
        std::array<uint32_t, 2> shaders = CreateShaders(sources);
        CreateProgram(shaders);
        CleanUpShaders(shaders);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(_rendererID);
    }

    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetUniformMat4(std::string name, glm::mat4 matrix) const
    {
        int location = glGetUniformLocation(_rendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUnifromInt(std::string name, int value) const
    {
        int location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::SetUniformFloat3(std::string name, glm::vec3 value) const
    {
        int location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::SetUniformFloat4(std::string name, glm::vec4 value) const
    {
        int location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.a);
    }

    std::string OpenGLShader::ReadShaderFile(const std::string& filePath)
    {
        try
        {
            return ReadShaderFileImpl(filePath);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    std::string OpenGLShader::ReadShaderFileImpl(const std::string& filePath)
    {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);

        if (!file.is_open()) {
            CB_CORE_LOG_ERROR("Unable to open Shader file: {0}", filePath);
            throw FailedToOpenFileError(filePath.c_str());
        }

        std::string result;

        file.seekg(0, std::ios::end);
        result.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&result[0], result.size());
        file.close();

        return result;
    }

    std::unordered_map<uint32_t, std::string> OpenGLShader::ProcessShaderFile(const std::string& source)
    {
        std::unordered_map<uint32_t, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos) {
            size_t eol = source.find_first_of("\r\n", pos);
            CB_CORE_ASSERT_TRUE(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            CB_CORE_ASSERT_TRUE(type == "vertex" || type == "fragment" || type == "pixel", "Invalid Shader type specified");

            size_t nextLinePos = source.find_first_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, 
                pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }



    std::array<uint32_t, 2> OpenGLShader::CreateShaders(std::unordered_map<uint32_t, std::string>& sources)
    {
        try
        {
            return CreateShadersImpl(sources);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    std::array<uint32_t, 2> OpenGLShader::CreateShadersImpl(std::unordered_map<uint32_t, std::string>& sources)
    {
        std::array<uint32_t, 2> shaders;

        int i = 0;
        for (auto& kv : sources) {
            uint32_t type = kv.first;
            std::string& source = kv.second;

            shaders[i] = CreateOpenGLShaderID(type, source);

            ++i;
        }
        return shaders;
    }

    void OpenGLShader::CleanUpShaders(std::array<uint32_t, 2> shaders)
    {
        for (auto& shader : shaders)
            glDetachShader(_rendererID, shader);
        for (auto& shader : shaders)
            glDeleteShader(shader);
    }

    uint32_t OpenGLShader::CreateOpenGLShaderID(uint32_t shaderType, const std::string& code)
    {
        try
        {
            return CreateOpenGLShaderIDImpl(shaderType, code);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    uint32_t OpenGLShader::CreateOpenGLShaderIDImpl(uint32_t shaderType, const std::string& code)
    {
        uint32_t shader = glCreateShader(shaderType);
        const char* cCode = code.c_str();
        glShaderSource(shader, 1, &cCode, NULL);
        glCompileShader(shader);

        int success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            int length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            std::vector<char> errorLog(length);
            glGetShaderInfoLog(shader, length, &length, &errorLog[0]);

            glDeleteShader(shader);

            throw VertexShaderCompilationsError(errorLog.data());
        }

        return shader;
    }

    uint32_t OpenGLShader::CreateProgram(std::array<uint32_t, 2> shaders)
    {
        try
        {
            return CreateProgramImpl(shaders);
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    uint32_t OpenGLShader::CreateProgramImpl(std::array<uint32_t, 2> shaders)
    {
        _rendererID = glCreateProgram();
        for (auto& shader : shaders)
            glAttachShader(_rendererID, shader);
        glLinkProgram(_rendererID);

        int success = 0;
        glGetProgramiv(_rendererID, GL_LINK_STATUS, (int*)&success);
        if (success == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(_rendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(_rendererID);
            for (auto& shader : shaders)
                glDeleteShader(shader);

            throw ProgramLinkingError(infoLog.data());
        }
    }

}
