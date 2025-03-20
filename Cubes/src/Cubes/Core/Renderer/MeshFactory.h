#pragma once
#include <array>
#include <stdint.h>
#include "Model.h"

namespace Cubes {

    class MeshFactory {
    public:

        inline static std::array<Vertex, 8> GetCubeVertices() 
        {
            return {{
                { glm::vec3(-1.0f, -1.0f, -1.0f),  glm::vec2(0.0f, 0.0f) }, // unten hinten links
                { glm::vec3( 1.0f, -1.0f, -1.0f),  glm::vec2(1.0f, 0.0f) }, // unten hinten rechts
                { glm::vec3( 1.0f,  1.0f, -1.0f),  glm::vec2(1.0f, 1.0f) }, // oben hinten rechts
                { glm::vec3(-1.0f,  1.0f, -1.0f),  glm::vec2(0.0f, 1.0f) }, // oben hinten links
                { glm::vec3(-1.0f, -1.0f,  1.0f),  glm::vec2(0.0f, 0.0f) }, // unten vorne links
                { glm::vec3( 1.0f, -1.0f,  1.0f),  glm::vec2(1.0f, 0.0f) }, // unten vorne rechts
                { glm::vec3( 1.0f,  1.0f,  1.0f),  glm::vec2(1.0f, 1.0f) }, // oben vorne rechts
                { glm::vec3(-1.0f,  1.0f,  1.0f),  glm::vec2(0.0f, 1.0f) }  // oben vorne links
            }};
        }

        inline static std::array<uint32_t, 3 * 12> GetCubeIndices()
        {
            return {
                // Front face
                4, 5, 6,
                6, 7, 4,

                // Back face
                0, 3, 2,
                2, 1, 0,

                // Left face
                0, 4, 7,
                7, 3, 0,

                // Right face
                1, 2, 6,
                6, 5, 1,

                // Top face
                3, 7, 6,
                6, 2, 3,

                // Bottom face
                0, 1, 5,
                5, 4, 0
            };
        }

        inline static std::array<Vertex, 4> GetQuadVertices() 
        {
            return {{
                { glm::vec3(-1.0f,  1.0f, 0.f),   glm::vec2(0.f, 1.f) }, //up, left   
                { glm::vec3( 1.0f,  1.0f, 0.f),   glm::vec2(1.f, 1.f) }, //up, right
                { glm::vec3( 1.0f, -1.0f, 0.f),   glm::vec2(1.f, 0.f) }, //down, right
                { glm::vec3(-1.0f, -1.0f, 0.f),   glm::vec2(0.f, 0.f) }    //down, left
            }};
        }

        inline static std::array<uint32_t, 2 * 3> GetQuadIndices()
        {
            return {
                0, 1, 2,
                2, 3, 0
            };
        }

    };

}