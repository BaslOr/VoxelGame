#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../Core/Renderer/RenderContext.h"
	
namespace Cubes {

	class OpenGLRenderContext : public RenderContext
	{
	public:
		OpenGLRenderContext(GLFWwindow* windowHandle);

		void SwapBuffers() override;

	private:
		GLFWwindow* _window;
	};

}
