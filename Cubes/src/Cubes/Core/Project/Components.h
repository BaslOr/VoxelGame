#pragma once
#include <glm/glm.hpp>
#include "../Renderer/Texture.h"
#include "../Renderer/Model.h"
#include "../Core.h"

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
        glm::mat4 Transform{ 1.f };

        TransformComponent() = default;
        TransformComponent(const glm::mat4& transform)
            : Transform(transform) { }
    };

    struct SpriteRendererComponent {
        Ref<Texture> Sprite;
        glm::vec4 Color{ 1.f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(Ref<Texture> sprite, glm::vec4& color)
            : Sprite(sprite), Color(color) { }
    };

    struct MeshRendererComponent {
        Ref<Model> Mesh;
        glm::vec4 Color;

        MeshRendererComponent() = default;
        MeshRendererComponent(Ref<Model> mesh, glm::vec4& color)
            : Mesh(mesh), Color(color) { }
    };

}