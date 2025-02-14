#pragma once
#include "../../Renderer/Buffer.h"

namespace Cubes {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* data, uint32_t size);
		~OpenGLVertexBuffer();

		inline void SetLayout(const BufferLayout& layout) override { _layout = layout; }
		inline const BufferLayout& GetLayout() const override { return _layout; }

		virtual void Bind() const;
		virtual void UnBind() const;

	private:
		RendererID _rendererID;
		BufferLayout _layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint16_t* data, uint16_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

	private:
		RendererID _rendererID;
	};

}
