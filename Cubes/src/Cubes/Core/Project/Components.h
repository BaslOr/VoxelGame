#pragma once
#include <glm/glm.hpp>

namespace Cubes {

    struct TagComponent 
    {
        TagComponent() = default;
        TagComponent(const std::string& tag)
            : Tag(tag) { }

        std::string Tag;
    };

    struct TransformComponent 
    {
        TransformComponent() = default;
        TransformComponent(const glm::mat4& transform)
            : Transform(transform) {}


        glm::mat4 Transform{ 1.f };
    };

}