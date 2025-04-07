#pragma once
#include "../Renderer/Camera.h"


namespace Cubes {

	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		~SceneCamera();

		void SetPerspective(float fov, float nearClip, float farClip) override;
		
		void SetViewportSize(uint32_t width, uint32_t height) override;

	private:
		void RecalculateProjection();

	private:
		float _perspectiveFOV = 45.0f;
		float _perspectiveNear = 0.1f, _perspectiveFar = 100.f;

		float _aspectRatio = 1.77f;
	};

}
