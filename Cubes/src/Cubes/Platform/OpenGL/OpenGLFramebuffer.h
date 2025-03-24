#pragma once 
#include "../../Core/Renderer/Framebuffer.h"

namespace Cubes {

    class OpenGLFramebuffer : public Framebuffer {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer();

        inline const FramebufferSpecification& GetSpecification() const override { return _specification; }
        inline uint32_t GetColorAttachmentID() const override { return _colorAttachmentID; }

        void Bind() const override;
        void Unbind() const override;

        void Recreate();

    private:
        uint32_t _rendererID;
        uint32_t _colorAttachmentID, _depthStencilAttachmentID;

        FramebufferSpecification _specification;
    };

}
