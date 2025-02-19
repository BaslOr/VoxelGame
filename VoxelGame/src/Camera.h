#pragma once
#include "Cubes/Application.h"
#include "Cubes/Renderer/Renderer.h"


namespace GameNamespace {

	class Camera : public Cubes::PerspectiveCamera
	{
	public:
		Camera(glm::vec3& position, float fov);

		void OnUpdate(Cubes::TimeStep timeStep);

	private:
		glm::vec3 _position;
		float _fov;
		

		float _movementSpeed = 1.f;
	};

}
