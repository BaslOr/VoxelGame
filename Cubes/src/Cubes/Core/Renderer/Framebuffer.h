#pragma once
#include "../Core.h"

namespace Cubes {
    
    struct FramebufferSpecification {
        uint32_t Width, Height;
        uint32_t Samples = 1;

        bool SwapChainTarget = false; // Metal(MacOS) specific
    };

    class Framebuffer {
    public:
        virtual const FramebufferSpecification& GetSpecification() const = 0;

        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

    private: 
        static Ref<Framebuffer> CreateFramebuffer(const FramebufferSpecification& spec);
    };

}