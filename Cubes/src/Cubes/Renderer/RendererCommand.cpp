#include "cbpch.h"
#include "RendererCommand.h"
#include "../Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cubes {

    RendererAPI* RendererCommand::_rendererAPI = new OpenGLRendererAPI();

}
