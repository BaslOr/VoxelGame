#include "cbpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Cubes {



	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	SceneCamera::~SceneCamera()
	{
	}

	void SceneCamera::SetPerspective(float fov, float nearClip, float farClip)
	{
		_perspectiveNear = nearClip;
		_perspectiveFar = farClip;
		_perspectiveFOV = fov;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		_aspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		_projectionMatrix = glm::perspective(glm::radians(_perspectiveFOV), _aspectRatio, _perspectiveNear, _perspectiveFar); //TODO: Check weather is Projection or is Orthographic
	}

}
