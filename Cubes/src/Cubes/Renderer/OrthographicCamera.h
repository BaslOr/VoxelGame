#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace Cubes {

    class OrthograpicCamera {
    public:
        OrthograpicCamera(float left, float right, float bottom, float top);
        ~OrthograpicCamera() = default;

        inline void SetRotation(float rotation) { _rotation = rotation; RecalculateProjectionViewMatrix(); }
        inline float GetRotation() const { return _rotation; }

        inline void SetPosition(glm::vec3 position) { _position = position; RecalculateProjectionViewMatrix(); }
        inline glm::vec3 GetPosition() const { return _position; }

        inline glm::mat4 GetViewProjection() { return _viewProjection; }

    private:
        void RecalculateProjectionViewMatrix();
    private:
        glm::mat4 _projection;
        glm::mat4 _view;
        glm::mat4 _viewProjection;

        glm::vec3 _position;

        float _rotation;
    };

}
