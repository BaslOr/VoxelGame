#include "Camera.h"


namespace GameNamespace {

    Camera::Camera(glm::vec3& position, float fov)
		: PerspectiveCamera(position, (float)Cubes::Application::Get().GetWindow().GetWidth() / (float)Cubes::Application::Get().GetWindow().GetHeight(), fov), _fov(fov), _position(position)
	{
		
	}

	void Camera::OnUpdate(Cubes::TimeStep deltaTime)
    {
        float moveDistance = _movementSpeed * deltaTime;

        if (Cubes::Input::IsKeyDown(CB_KEY_W))
            _position.z -= .1f;
        else if (Cubes::Input::IsKeyDown(CB_KEY_S))
            _position.z += .1f;
        if (Cubes::Input::IsKeyDown(CB_KEY_D))
            _position.x += .1f;
        else if (Cubes::Input::IsKeyDown(CB_KEY_A))
            _position.x -= .1f;
        if (Cubes::Input::IsKeyDown(CB_KEY_SPACE))
            _position.y += .1f;
        else if (Cubes::Input::IsKeyDown(CB_KEY_LEFT_SHIFT))
            _position.y -= .1f;

        SetPosition(_position);
	}

}
