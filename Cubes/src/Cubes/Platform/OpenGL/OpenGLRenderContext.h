#pragma once
#include "../../Renderer/RenderContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
	
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
