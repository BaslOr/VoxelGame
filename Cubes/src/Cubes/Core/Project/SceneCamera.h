#pragma once
#include "../Renderer/Camera.h"


namespace Cubes {

    class SceneCamera : public Camera
    {
    public:
        enum class ProjectionType { Perspective = 0, Orthographic = 1 };
    public:
        SceneCamera();
        ~SceneCamera();

        void SetPerspective(float fov, float nearClip, float farClip) override;
        void SetOrthographic(float size, float nearClip, float farClip) override;
        
        void SetViewportSize(uint32_t width, uint32_t height) override;

        inline ProjectionType GetProjectionType() const { return _projectionType; }
        inline void SetProjectionType(ProjectionType projectionType) { _projectionType = projectionType;  RecalculateProjection(); }

        inline float GetPerspectiveFov() const { return _perspectiveFOV; }
        inline void SetPerspectiveFov(float fov) { _perspectiveFOV = fov; RecalculateProjection(); }
        inline float GetPerspectiveNear() const { return _perspectiveNear; }
        inline void SetPerspectiveNear(float perspectiveNear) { _perspectiveNear = perspectiveNear; RecalculateProjection(); }
        inline float GetPerspectiveFar() const { return _perspectiveFar; }
        inline void SetPerspectiveFar(float perspectiveFar) { _perspectiveFar = perspectiveFar;  RecalculateProjection(); }

        inline float GetOrthographicSize() const { return _orthographicSize; }
        inline void SetOrthographicSize(float size) { _orthographicSize = size; RecalculateProjection(); }
        inline float GetOrthographicNear() const { return _orthographicFar; }
        inline void SetOrthographicNear(float orthographicNear) { _orthographicNear = orthographicNear; RecalculateProjection(); }
        inline float GetOrthographicFar() const { return _orthographicFar; }
        inline void SetOrthographicFar(float orthographicFar) { _orthographicFar = orthographicFar; RecalculateProjection(); }

    private:
        void RecalculateProjection();

        void CalculatePerspective();
        void CalculateOrthographic();

    private:
        ProjectionType _projectionType = ProjectionType::Perspective;
        float _aspectRatio = 1.77f;

        float _perspectiveFOV = 45.0f;
        float _perspectiveNear = 0.1f, _perspectiveFar = 1000.f;

        float _orthographicSize = 10.0f;
        float _orthographicNear = 0.1f, _orthographicFar = 10.f;

    };

}
