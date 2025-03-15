#include "cbpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Cubes {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        try
        {
            switch (type)
            {
            case Cubes::ShaderDataType::Float:     return GL_FLOAT;
            case Cubes::ShaderDataType::Float2:    return GL_FLOAT;
            case Cubes::ShaderDataType::Float3:    return GL_FLOAT;
            case Cubes::ShaderDataType::Float4:    return GL_FLOAT;
            case Cubes::ShaderDataType::Mat3:      return GL_FLOAT;
            case Cubes::ShaderDataType::Mat4:      return GL_FLOAT;
            case Cubes::ShaderDataType::Int:       return GL_INT;
            case Cubes::ShaderDataType::Int2:      return GL_INT;
            case Cubes::ShaderDataType::Int3:      return GL_INT;
            case Cubes::ShaderDataType::Int4:      return GL_INT;
            case Cubes::ShaderDataType::Bool:      return GL_BOOL;
            }

            throw UnkownShaderDataTypeError();
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }

    }
    
 
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &_rendererID);
        glBindVertexArray(_rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &_rendererID);
    }

    inline void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(_rendererID);
    }

    inline void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> vertexBuffer)
    {
        glBindVertexArray(_rendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
            ++index;
        }

        _vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> indexBuffer)
    {
        glBindVertexArray(_rendererID);
        indexBuffer->Bind();

        _indexBuffer = indexBuffer;
    }



}
