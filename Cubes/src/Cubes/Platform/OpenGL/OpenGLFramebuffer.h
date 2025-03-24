#pragma once 
#include "../../Core/Renderer/Framebuffer.h"

namespace Cubes {

    class OpenGLFramebuffer : public Framebuffer {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer();

        void Recreate();

    private:
        uint32_t _rendererID;
        uint32_t _colorAttachmentID, _depthStencilAttachmentID;

        FramebufferSpecification _specification;
    };

}
