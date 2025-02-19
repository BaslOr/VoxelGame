#pragma once
#include <Cubes/Renderer/PerspectiveCamera.h>
#include <Cubes/Input.h>
#include <Cubes/Application.h>

namespace GameNamespace {

	class Camera : public Cubes::PerspectiveCamera
	{
	public:
		Camera(glm::vec3& position, float fov);

		void OnUpdate();

	private:
		glm::vec3 _position;
		float _fov;
	};

}
