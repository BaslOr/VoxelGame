#pragma once
#include "../../Renderer/VertexArray.h"

namespace Cubes {

    class OpenGLVertexArray : public VertexArray{
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        inline  void Bind() const override;
        inline void UnBind() const override;

        void AddVertexBuffer(std::shared_ptr<VertexBuffer> vertexBuffer) override;
        void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer) override;

        inline std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const { return _vertexBuffers; }
        inline std::shared_ptr<IndexBuffer> GetIndexBuffer() const { return _indexBuffer; }

    private:
        RendererID _rendererID;
        std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
        std::shared_ptr<IndexBuffer> _indexBuffer;
    };

}
