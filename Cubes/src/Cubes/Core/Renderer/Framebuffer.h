#pragma once
#include "../Core.h"

namespace Cubes {
    
    struct FramebufferSpecification {
        uint32_t Width, Height;
        uint32_t Samples = 1;

        bool SwapChainTarget = false; // Metal(MacOS) specific

        bool operator!=(FramebufferSpecification const& other) {
            return Width == other.Width &&
                Height == other.Height &&
                Samples == other.Samples &&
                SwapChainTarget == other.SwapChainTarget;
        }
    };

    class Framebuffer {
    public:
        virtual const FramebufferSpecification& GetSpecification() const = 0;
        virtual uint32_t GetColorAttachmentID() const = 0;

        virtual void Invalidate(const FramebufferSpecification& spec) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Ref<Framebuffer> Create(const FramebufferSpecification& specification);

    private: 
        static Ref<Framebuffer> CreateFramebuffer(const FramebufferSpecification& spec);
    };

}