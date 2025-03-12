#include "cbpch.h"
#include "OpenGLRenderContext.h"
#include "../../Core/Core.h"
#include "../../Core/Error/Error.h"

namespace Cubes {

    OpenGLRenderContext::OpenGLRenderContext(GLFWwindow* windowHandle)
        : _window(windowHandle)
    {
        CreateOpenGLRenderContext();
    }
    void OpenGLRenderContext::SwapBuffers()
    {
        glfwSwapBuffers(_window);
    }

    void OpenGLRenderContext::CreateOpenGLRenderContext()
    {
        glfwMakeContextCurrent(_window);
        int succes = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!succes)
            throw VendorAPIInitilizationError("glad");
    }

}
