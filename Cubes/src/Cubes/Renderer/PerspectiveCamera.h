#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Events/ApplicationEvent.h"

namespace Cubes {

    class PerspectiveCamera {
    public:
        PerspectiveCamera() {}
        PerspectiveCamera(glm::vec3& position, float aspectRatio, float fov);

        inline void SetFOV(float fov) { 
            _fov = fov;
            _projectionMatrix = glm::perspective(_fov, _aspectRatio, 0.1f, 100.f);
            RecalculateViewProjectionMatrix();
        }
        inline float GetFOV() const { return _fov; }

        inline glm::mat4 GetViewProjection() const { return _viewProjectionMatrix; }

        inline void SetPosition(glm::vec3& position) { _position = position; RecalculateViewProjectionMatrix(); }
        inline glm::vec3 GetPosition() const { return _position; }

        inline void SetDirection(glm::vec3 direction) { _direction = direction; RecalculateViewProjectionMatrix(); }
        inline glm::vec3 GetDirection() const { return _direction; }


        void OnEvent(Event& event);

    protected:
        void CalculateViewProjectionMatrix();
        void RecalculateViewProjectionMatrix();

        bool OnWindowResize(WindowResizeEvent& event);

    protected:
        glm::vec3 _position;
        glm::vec3 _target;
        glm::vec3 _front;
        glm::vec3 _direction;
        glm::vec3 _right;
        glm::vec3 _up;
        float _fov;
        float _aspectRatio;
        
        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;
        glm::mat4 _viewProjectionMatrix;
    };

}