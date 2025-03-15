#include "cbpch.h"
#include "PerspectiveCamera.h"
#include "../Events/ApplicationEvent.h"
#include "../Core.h"

namespace Cubes {


    PerspectiveCamera::PerspectiveCamera(glm::vec3& position, float aspectRatio, float fov)
        : _projectionMatrix(1.f), _viewMatrix(1.f), _front(0.f, 0.f, -1.f), _position(position), _target(0.f), _fov(fov), _up(glm::vec3(0.f, 1.f, 0.f))
    {
        _projectionMatrix = glm::perspective(fov, aspectRatio, 0.1f, 100.f);


        RecalculateViewProjectionMatrix();
    }

    void PerspectiveCamera::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(CB_BIND_EVENT_FUNC(PerspectiveCamera::OnWindowResizeEvent));
    }

    void PerspectiveCamera::CalculateViewProjectionMatrix()
    {
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }

    void PerspectiveCamera::RecalculateViewProjectionMatrix()
    {
        _front = glm::normalize(_direction);
        _right = glm::normalize(glm::cross(_front, _up));
        _viewMatrix = glm::lookAt(_position, _position + _front, _up);
        CalculateViewProjectionMatrix();
    }

    bool PerspectiveCamera::OnWindowResizeEvent(WindowResizeEvent& event)
    {
        _aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
        _projectionMatrix = glm::perspective(_fov, _aspectRatio, 0.1f, 100.f);
        CalculateViewProjectionMatrix();

        return false;
    }

}
