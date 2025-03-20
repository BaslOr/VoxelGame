#pragma once
#include <array>
#include <stdint.h>

namespace Cubes {

    class MeshFactory {
    public:

        inline static std::array<float, 5 * 8> GetCubeVertices() 
        {
            return {
                // Position          // TexCoord
                -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, // 0
                 1.0f, -1.0f, -1.0f,  1.0f, 0.0f, // 1
                 1.0f,  1.0f, -1.0f,  1.0f, 1.0f, // 2
                -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, // 3
                -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, // 4
                 1.0f, -1.0f,  1.0f,  1.0f, 0.0f, // 5
                 1.0f,  1.0f,  1.0f,  1.0f, 1.0f, // 6
                -1.0f,  1.0f,  1.0f,  0.0f, 1.0f  // 7
            };
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

        inline static std::array<float, 5 * 4> GetQuadVertices() 
        {
            return {
                //Positions           TexCoords
                -1.0f,  1.0f, 0.f,    0.f, 1.f, //up, left   
                 1.0f,  1.0f, 0.f,    1.f, 1.f, //up, right
                 1.0f, -1.0f, 0.f,    1.f, 0.f, //down, right
                -1.0f, -1.0f, 0.f,    0.f, 0.f  //down, left
            };

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