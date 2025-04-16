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
        glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const glm::vec3& position)
            : Position(position) { }

        [[nodiscard]] inline glm::mat4 GetTransform() const {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1, 0, 0 }) *
                glm::rotate(glm::mat4(1.0f), Rotation.y, { 0, 1, 0 }) *
                glm::rotate(glm::mat4(1.0f), Rotation.z, { 0, 0, 1 });

            return glm::translate(glm::mat4(1.0f), Position) *
                rotation *
                glm::scale(glm::mat4(1.0f), Scale);
        }
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
        Ref<Texture> Sprite = Texture::Create("../Cubes/resources/textures/DefaultTexture.png");
        glm::vec4 Color{ 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(Ref<Texture> sprite, glm::vec4& color)
            : Sprite(sprite), Color(color) { }
    };

    struct MeshRendererComponent 
    {
        Ref<Model> Mesh; //TODO: Add default Meshf
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