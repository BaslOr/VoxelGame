#pragma once
#include <Cubes.h>


class Camera : public Cubes::PerspectiveCamera
{
public:
	Camera();
	Camera(glm::vec3& position, float fov);

	void OnUpdate(Cubes::TimeStep timeStep);

private:
	glm::vec3 _position;
	float _fov;

	float _lastMouseX = 0.f, _lastMouseY = 0.f;
	float _yaw = -90.f, _pitch = 0.f;
	

	float _movementSpeed = 0.02f;
	float _mouseSensitivity = 0.05f;
};

