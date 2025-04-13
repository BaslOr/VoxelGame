#pragma once
#include <glm/glm.hpp>

namespace Cubes {

    class Camera {
    public:
        Camera() = default;
        Camera(const glm::mat4& projection)
            : _projectionMatrix(projection) { }
        virtual ~Camera() = default;

        virtual void SetPerspective(float fov, float nearClip, float farClip) = 0;
        virtual void SetOrthographic(float size, float nearClip, float farClip) = 0;

        virtual void SetViewportSize(uint32_t width, uint32_t height) = 0;

        inline const glm::mat4& GetProjection() { return _projectionMatrix; }

    protected:
        glm::mat4 _projectionMatrix = glm::mat4(1.f);
    };

}
