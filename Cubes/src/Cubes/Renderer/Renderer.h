#pragma once

namespace Cubes {

	enum class RenderAPI {
		None = 0, OpenGL = 1, Vulkan = 2 
	};

	using RendererID = uint32_t;



	class Renderer {
	public:

		inline static RenderAPI GetRenderAPI() { return RenderAPI::OpenGL; } //Query RenderAPI 

	private:
	};

}