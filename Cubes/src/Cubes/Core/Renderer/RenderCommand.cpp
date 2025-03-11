#include "cbpch.h"
#include "RenderCommand.h"
#include "../../Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cubes {

    RendererAPI* RenderCommand::_rendererAPI = new OpenGLRendererAPI();

}
