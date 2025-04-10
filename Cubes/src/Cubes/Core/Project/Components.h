#pragma once
#include <glm/glm.hpp>

#include "../Core.h"

#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include "../Renderer/Texture.h"
#include "../Renderer/Model.h"

namespace Cubes {

    struct TagComponent 
    {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const std::string& tag)
            : Tag(tag) { }
    };

    struct TransformComponent 
    {
        glm::mat4 Transform{ 1.0f };

        TransformComponent() = default;
        TransformComponent(const glm::mat4& transform)
            : Transform(transform) { }
    };

    struct NativeScriptComponent
    {
        ScriptableEntity* Instance = nullptr;



        ScriptableEntity*(*InstantiateScript)();
        void(*DestroyScript)(NativeScriptComponent*);

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScript = [](NativeScriptComponent* nsc) { delete (T*)nsc->Instance; nsc->Instance = nullptr; };
        }
    };

    struct SpriteRendererComponent
    {
        Ref<Texture> Sprite; //TODO: Add default Sprite
        glm::vec4 Color{ 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(Ref<Texture> sprite, glm::vec4& color)
            : Sprite(sprite), Color(color) { }
    };

    struct MeshRendererComponent 
    {
        Ref<Model> Mesh; //TODO: Add default Mesh
        glm::vec4 Color{ 1.0 };

        MeshRendererComponent() = default;
        MeshRendererComponent(Ref<Model> mesh, glm::vec4& color)
            : Mesh(mesh), Color(color) { }
    };

    struct CameraComponent 
    {
        SceneCamera Camera;
        bool Primary = true; //TODO: Should be handled by Scene

        CameraComponent() = default;
    };

}