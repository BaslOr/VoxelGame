#include "cbpch.h"
#include "OrthographicCamera.h"

namespace Cubes {

	OrthograpicCamera::OrthograpicCamera(float left, float right, float bottom, float top)
		: _projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _view(1.0f)
	{
		_viewProjection = _projection * _view;
	}

	void OrthograpicCamera::RecalculateProjectionViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.f), _position) *
			glm::rotate(glm::mat4(1.f), glm::radians(_rotation), glm::vec3(0, 0, 1));

		_view = glm::inverse(transform);
		_viewProjection = _projection * _view;

	}

}
