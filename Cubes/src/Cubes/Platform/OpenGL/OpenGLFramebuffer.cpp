#include "cbpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Cubes {

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
        : _specification(spec)
    {
        Invalidate(_specification);
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        DeleteRecources();
    }

    void OpenGLFramebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);
    }

    void OpenGLFramebuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Invalidate(const FramebufferSpecification& specification) 
    {
        FramebufferSpecification spec = specification;
        if (spec.Width != _specification.Width) {
            _specification = spec;
            DeleteRecources();
            Recreate();
        }
    }

    void OpenGLFramebuffer::DeleteRecources()
    {
        glDeleteFramebuffers(1, &_rendererID);
        glDeleteTextures(1, &_colorAttachmentID);
        glDeleteTextures(1, &_depthStencilAttachmentID);
    }

    void OpenGLFramebuffer::Recreate()
    {
        glGenFramebuffers(1, &_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);

        glGenTextures(1, &_colorAttachmentID);
        glBindTexture(GL_TEXTURE_2D, _colorAttachmentID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specification.Width, _specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachmentID, 0);

        glGenTextures(1, &_depthStencilAttachmentID);
        glBindTexture(GL_TEXTURE_2D, _depthStencilAttachmentID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _specification.Width, _specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthStencilAttachmentID, 0);

        CB_CORE_ASSERT_TRUE(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}