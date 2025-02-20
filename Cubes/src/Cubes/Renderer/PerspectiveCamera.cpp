#include "cbpch.h"
#include "PerspectiveCamera.h"
#include "../Events/ApplicationEvent.h"
#include "../Core.h"

namespace Cubes {

    const glm::vec3 CAMERA_UP = glm::vec3(0.f, 1.f, 0.f);

    PerspectiveCamera::PerspectiveCamera(glm::vec3& position, float aspectRatio, float fov)
        : _projectionMatrix(1.f), _viewMatrix(1.f), _front(0.f, 0.f, -1.f), _position(position), _target(0.f), _fov(fov)
    {
        _projectionMatrix = glm::perspective(fov, aspectRatio, 0.1f, 100.f);


        RecalculateViewProjectionMatrix();
    }

    void PerspectiveCamera::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(
            [this](WindowResizeEvent& event) -> bool { return OnWindowResize(event); }
        );
    }

    void PerspectiveCamera::CalculateViewProjectionMatrix()
    {
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }

    void PerspectiveCamera::RecalculateViewProjectionMatrix()
    {
        _direction = glm::normalize(_position - _target);
        _right = glm::normalize(glm::cross(CAMERA_UP, _direction));

        _viewMatrix = glm::lookAt(_position, _position + _front, CAMERA_UP);

        CalculateViewProjectionMatrix();
    }

    bool PerspectiveCamera::OnWindowResize(WindowResizeEvent& event)
    {
        _aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
        _projectionMatrix = glm::perspective(_fov, _aspectRatio, 0.1f, 100.f);
        CalculateViewProjectionMatrix();

        return false;
    }

}