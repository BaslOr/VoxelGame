#include "cbpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Cubes {



    SceneCamera::SceneCamera()
    {
        RecalculateProjection();
    }

    SceneCamera::~SceneCamera()
    {
    }

    void SceneCamera::SetPerspective(float fov, float nearClip, float farClip)
    {
        _projectionType = ProjectionType::Perspective;

        _perspectiveFOV = fov;
        _perspectiveNear = nearClip;
        _perspectiveFar = farClip;

        RecalculateProjection();
    }

    void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
    {
        _projectionType = ProjectionType::Orthographic;

        _orthographicSize = size;
        _orthographicNear = nearClip;
        _orthographicFar = farClip;

        RecalculateProjection();
    }

    void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
    {
        _aspectRatio = (float)width / (float)height;
        RecalculateProjection();
    }

    void SceneCamera::RecalculateProjection()
    {
        switch (_projectionType)
        {
        case ProjectionType::Perspective:
            CalculatePerspective();
            break;
        case ProjectionType::Orthographic:
            CalculateOrthographic();
            break;
        }
    }

    void SceneCamera::CalculatePerspective()
    {
        _projectionMatrix = glm::perspective(glm::radians(_perspectiveFOV), _aspectRatio, _perspectiveNear, _perspectiveFar);
    }

    void SceneCamera::CalculateOrthographic()
    {
        float orthoLeft = -_orthographicSize * _aspectRatio * 0.5f;
        float orthoRight = _orthographicSize * _aspectRatio * 0.5f;
        float orthoBottom = -_orthographicSize * 0.5f;
        float orthoTop = _orthographicSize * 0.5f;

        _projectionMatrix = glm::ortho(orthoLeft, orthoRight,
            orthoBottom, orthoTop, _orthographicNear, _orthographicFar);
    }

}
