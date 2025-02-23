#include "cbpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "../../Core.h"


namespace Cubes {

    static uint32_t ShaderTypeFromString(const std::string& type) {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment")
            return GL_FRAGMENT_SHADER;
        if (type == "pixel")
            return GL_FRAGMENT_SHADER;

        CB_CORE_ASSERT(false, "Unkown shader type");
        return 0;
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
        const char* cVertexCode = vertexCode.c_str();
        const char* cFragmentCode = fragmentCode.c_str();

        int success = 0;

        uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
        uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

        _rendererID = glCreateProgram();
        glAttachShader(_rendererID, vertexShader);
        glAttachShader(_rendererID, fragmentShader);
        glLinkProgram(_rendererID);
        glGetProgramiv(_rendererID, GL_LINK_STATUS, (int*)&success);
        if (success == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(_rendererID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(_rendererID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            CB_CORE_ERROR("{0}", infoLog.data());
            CB_CORE_ASSERT(false, "Failed to Link ShaderProgram");
        }

        glDetachShader(_rendererID, vertexShader);
        glDetachShader(_rendererID, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(_rendererID);
    }

    std::string OpenGLShader::ReadShaderFile(const std::string& filePath)
    {
        std::ifstream file(filePath, std::ios::in | std::ios::binary);

        if (!file.is_open()) {
            CB_CORE_ERROR("Unable to open Shader file: {0}", filePath);
            return nullptr;
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
            CB_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            CB_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Invalid Shader type specified");

            size_t nextLinePos = source.find_first_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, 
                pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(std::unordered_map<uint32_t, std::string>& sources)
    {
        uint32_t shaders[2];

        int i = 0;
        for (auto& kv : sources) {
            uint32_t type = kv.first;
            std::string& source = kv.second;

            shaders[i] = CompileShader(type, source);

            ++i;
        }

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


            CB_CORE_ERROR("{0}", infoLog.data());
            CB_CORE_ASSERT(false, "Failed to Link ShaderProgram");
        }

        for (auto& shader : shaders)
            glDetachShader(_rendererID, shader);
        for (auto& shader : shaders)
            glDeleteShader(shader);
    }

    uint32_t OpenGLShader::CompileShader(uint32_t shaderType, const std::string& code)
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

            CB_CORE_ERROR("{0}", errorLog.data());
            CB_CORE_ASSERT(false, "Failed to compile Vertex Shader");
        }

        return shader;
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
        glUseProgram(_rendererID);
        int location = glGetUniformLocation(_rendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::SetUnifromInt(std::string name, int value) const
    {
        glUseProgram(_rendererID);
        int location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::SetUniformFloat3(std::string name, glm::vec3 value) const
    {
        glUseProgram(_rendererID);
        int location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::SetUniformFloat4(std::string name, glm::vec4 value) const
    {
        glUseProgram(_rendererID);
        int location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.a);
    }

}
