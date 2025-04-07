#pragma once
#include <Cubes.h>
#include "Cubes/Core/Renderer/PerspectiveCamera.h"

namespace Cubes {

	class CameraController : public PerspectiveCamera
	{
	public:
		CameraController() = default;
		CameraController(glm::vec3& position, float fov);

		void OnUpdate(TimeStep timeStep);

	private:
		glm::vec3 _position;
		float _fov;

		float _lastMouseX = 0.f, _lastMouseY = 0.f;
		float _yaw = -90.f, _pitch = 0.f;


		float _movementSpeed = 0.02f;
		float _mouseSensitivity = 0.05f;
	};

}
