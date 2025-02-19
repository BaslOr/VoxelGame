#pragma once
#include <glm/glm.hpp>
#include "../Events/ApplicationEvent.h"

namespace Cubes {

    class PerspectiveCamera {
    public:
        PerspectiveCamera() {}
        PerspectiveCamera(glm::vec3 position, float aspectRatio, float fov);

        inline void SetFOV(float fov) { _fov = fov; }
        inline float GetFOV() const { return _fov; }

        inline glm::mat4 GetViewProjection() const { return _viewProjectionMatrix; }

        inline void SetPosition(glm::vec3& position) { _position = position; RecalculateViewProjectionMatrix(); }
        inline glm::vec3 GetPosition() const { return _position; }

        inline void SetRotation(float rotation) { _rotation = rotation; RecalculateViewProjectionMatrix(); }
        inline float GetRotation() const { return _rotation; }


        void OnEvent(Event& event);

    private:
        void CalculateViewProjectionMatrix();
        void RecalculateViewProjectionMatrix();

        bool OnWindowResize(WindowResizeEvent& event);

    private:
        glm::vec3 _position;
        glm::vec3 _target;
        glm::vec3 _front;
        glm::vec3 _direction;
        float _fov;
        float _rotation;
        
        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;
        glm::mat4 _viewProjectionMatrix;
    };

}