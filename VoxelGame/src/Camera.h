#pragma once
#include "Cubes/Core/Application.h"
#include "Cubes/Core/Renderer/Renderer.h"


namespace GameNamespace {

	class Camera : public Cubes::PerspectiveCamera
	{
	public:
		Camera(glm::vec3& position, float fov);

		void OnUpdate(Cubes::TimeStep timeStep);

	private:
		glm::vec3 _position;
		float _fov;

		float _lastMouseX = 0.f, _lastMouseY = 0.f;
		float _yaw = -90.f, _pitch = 0.f;
		

		float _movementSpeed = 0.01f;
		float _mouseSensitivity = 0.05f;
	};

}
