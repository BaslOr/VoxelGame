#include "cbpch.h"
#include "OpenGLRenderContext.h"
#include "../../Core.h"

namespace Cubes {

    OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* windowHandle)
        : _window(windowHandle)
    {
        glfwMakeContextCurrent(_window);
        int succes = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        CB_CORE_ASSERT(succes, "Failed to initialized Glad!");
    }
    void OpenGLRenderContext::SwapBuffers()
    {
        glfwSwapBuffers(_window);
    }

}
