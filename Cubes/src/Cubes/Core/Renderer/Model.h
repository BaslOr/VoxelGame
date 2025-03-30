
#pragma once
#include "Texture.h"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

namespace Cubes {

    struct Vertex {
        glm::vec3 Position;
        glm::vec2 TexCoord;

        bool operator==(const Vertex& other) const {
            return Position == other.Position && TexCoord == other.TexCoord;
        }
    };

    struct Model {
        std::vector<Vertex> Vertices;
        std::vector<uint32_t> Indices;
        Ref<Texture> Texture;
    };

}

namespace std {
    template<> struct hash<Cubes::Vertex> {
        size_t operator()(const Cubes::Vertex& vertex) const {
            size_t posHash = std::hash<glm::vec3>()(vertex.Position);
            size_t texHash = std::hash<glm::vec2>()(vertex.TexCoord);

            // Standardm‰ﬂiges Hash-Mixing
            return posHash ^ (texHash + 0x9e3779b9 + (posHash << 6) + (posHash >> 2));
        }
    };
}
