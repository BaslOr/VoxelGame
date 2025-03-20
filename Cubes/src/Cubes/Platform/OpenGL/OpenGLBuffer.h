#pragma once
#include "../../Core/Renderer/Buffer.h"

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
		uint32_t _rendererID;
		BufferLayout _layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* data, uint32_t count);
		~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void UnBind() const;

		inline uint32_t GetCount() const override { return _count; }

	private:
		uint32_t _rendererID;
		uint32_t _count;
	};

}
