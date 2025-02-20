#include "Camera.h"


namespace GameNamespace {

    Camera::Camera(glm::vec3& position, float fov)
		: PerspectiveCamera(position, (float)Cubes::Application::Get().GetWindow().GetWidth() / (float)Cubes::Application::Get().GetWindow().GetHeight(), fov), _fov(fov), _position(position)
	{
        SetDirection(glm::vec3(0.f));
	}

    void Camera::OnUpdate(Cubes::TimeStep deltaTime)
    {
        bool doMouseCalculations = false;
        if (Cubes::Input::IsMouseButtonDown(CB_MOUSE_BUTTON_RIGHT)) {
            Cubes::Application::Get().GetWindow().SetInputModeCursor(true);
            doMouseCalculations = true;
        }
        else
            Cubes::Application::Get().GetWindow().SetInputModeCursor(false);


        float moveDistance = _movementSpeed * deltaTime;


        if (Cubes::Input::IsKeyDown(CB_KEY_W))
            _position += _front * _movementSpeed;
        else if (Cubes::Input::IsKeyDown(CB_KEY_S))
            _position -= _front * _movementSpeed;
        if (Cubes::Input::IsKeyDown(CB_KEY_D))
            _position += _right * _movementSpeed;
        else if (Cubes::Input::IsKeyDown(CB_KEY_A))
            _position -= _right * _movementSpeed;
        if (Cubes::Input::IsKeyDown(CB_KEY_SPACE))
            _position.y += _movementSpeed;
        else if (Cubes::Input::IsKeyDown(CB_KEY_LEFT_SHIFT))
            _position.y -= _movementSpeed;

        SetPosition(_position);

        if (!doMouseCalculations)
            return;

        float currentXPosition = Cubes::Input::GetMouseX();
        float currentYPosition = Cubes::Input::GetMouseY();
        float deltaX = currentXPosition - _lastMouseX;
        float deltaY = _lastMouseY - currentYPosition;
        _lastMouseX = currentXPosition;
        _lastMouseY = currentYPosition;

        _yaw += deltaX * _mouseSensitivity;
        _pitch += deltaY * _mouseSensitivity;

        _pitch = glm::clamp(_pitch, -90.f, 90.f);

        glm::vec3 direction;
        direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        direction.y = sin(glm::radians(_pitch));
        direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        _front = glm::normalize(direction);

        SetDirection(direction);
	}

}
