#pragma once
#include <stdint.h>

#include "../Core.h"
#include "../Error/Error.h"

namespace Cubes {

    class UnkownShaderDataTypeError : public Error {
    public:
        UnkownShaderDataTypeError()
            : Error("Unkown shader data type")
        {}
    };

    enum class ShaderDataType 
    {
        None = 0, 
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };

    static uint32_t GetShaderDataTypeSize(ShaderDataType type) {
        try
        {
            switch (type)
            {
                case Cubes::ShaderDataType::Float:     return 4;
                case Cubes::ShaderDataType::Float2:    return 4 * 2;
                case Cubes::ShaderDataType::Float3:    return 4 * 3;
                case Cubes::ShaderDataType::Float4:    return 4 * 4;
                case Cubes::ShaderDataType::Mat3:      return 4 * 3 * 3;
                case Cubes::ShaderDataType::Mat4:      return 4 * 4 * 4;
                case Cubes::ShaderDataType::Int:       return 4;
                case Cubes::ShaderDataType::Int2:      return 4 * 2;
                case Cubes::ShaderDataType::Int3:      return 4 * 3;
                case Cubes::ShaderDataType::Int4:      return 4 * 4;
                case Cubes::ShaderDataType::Bool:      return 4;
            }

            throw UnkownShaderDataTypeError();
        }
        catch (const Error& error)
        {
            CB_CORE_LOG_ERROR("{0}", error.what());
        }
    }

    struct BufferElement 
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Offset;
        uint32_t Size;
        bool Normalized;

        BufferElement() = default;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Normalized(normalized), Size(GetShaderDataTypeSize(type)), Offset(0)
        { }

        uint32_t GetComponentCount() const {
            try
            {
                return GetComponentCountFromTable();
            }
            catch (const Error& error)
            {
                CB_CORE_LOG_ERROR("{0}", error.what());
            }
        }

        uint32_t GetComponentCountFromTable() const {
            switch (Type)
            {
                case Cubes::ShaderDataType::Float:    return 1;
                case Cubes::ShaderDataType::Float2:   return 2;
                case Cubes::ShaderDataType::Float3:   return 3;
                case Cubes::ShaderDataType::Float4:   return 4;
                case Cubes::ShaderDataType::Mat3:     return 3 * 3;
                case Cubes::ShaderDataType::Mat4:     return 4 * 4;
                case Cubes::ShaderDataType::Int:      return 1;
                case Cubes::ShaderDataType::Int2:     return 2;
                case Cubes::ShaderDataType::Int3:     return 3;
                case Cubes::ShaderDataType::Int4:     return 4;
                case Cubes::ShaderDataType::Bool:     return 1;
            }

            throw UnkownShaderDataTypeError();
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;

        BufferLayout(const std::initializer_list<BufferElement>& elements)
            :_elements(elements)
        {
            CalculateOffsetAndStride();
        }

        inline const std::vector<BufferElement> GetLayout() const { return _elements; }
        inline uint32_t GetStride() const { return _stride; }

        std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
        std::vector<BufferElement>::iterator end() { return _elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }
    private:
        inline void CalculateOffsetAndStride() {
            uint32_t offset = 0;
            uint32_t stride = 0;
            for (auto& element : _elements) {
                element.Offset = offset;
                offset += element.Size;
                _stride += element.Size;
            }
        }

    private:
        std::vector<BufferElement> _elements;
        uint32_t _stride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;
        
        static Ref<VertexBuffer> Create(void* data, uint32_t size);

    private:
        static Ref<VertexBuffer> SelectAPIAndCreate(void* data, uint32_t size);
    };

    /////////////////////////////////////////////////////////////////////////////
    //////////////////////IndexBuffer////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////


    class IndexBuffer 
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual uint16_t GetCount() const = 0;

        static Ref<IndexBuffer> Create(uint16_t* data, uint16_t count);

    private:
        static Ref<IndexBuffer> SelectAPIAndCreate(uint16_t* data, uint16_t count);
    };

}
