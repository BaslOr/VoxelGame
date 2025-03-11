#pragma once
#include "../../Core/Renderer/Texture.h"

namespace Cubes {

	class OpenGLTexture2D : public Texture {
	public:
		OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D();

		inline uint32_t GetWidth() const override { return _width; }
		inline uint32_t GetHeight() const override { return _height; }

		void Bind(uint32_t slot = 0) const override;

	private:
		uint32_t _width, _height;

		uint32_t _rendererID;

	};

}
