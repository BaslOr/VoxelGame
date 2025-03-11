#pragma once
#include "../../Core/Renderer/VertexArray.h"

namespace Cubes {

    class OpenGLVertexArray : public VertexArray{
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        inline  void Bind() const override;
        inline void UnBind() const override;

        void AddVertexBuffer(Ref<VertexBuffer> vertexBuffer) override;
        void SetIndexBuffer(Ref<IndexBuffer> indexBuffer) override;

        inline std::vector<Ref<VertexBuffer>> GetVertexBuffers() const override { return _vertexBuffers; }
        inline Ref<IndexBuffer> GetIndexBuffer() const override { return _indexBuffer; }

    private:
        uint32_t _rendererID;
        std::vector<Ref<VertexBuffer>> _vertexBuffers;
        Ref<IndexBuffer> _indexBuffer;
    };

}
