#pragma once
#include "../Error/Error.h"
#include "../Renderer/Model.h"
#include "../Core.h"

#include "../../Vendor/TinyOBJLoader/tiny_obj_loader.h"

namespace Cubes {

    class ModelLoader {
    public:

        inline static Model LoadModel(const std::string& modelPath, const std::string& texturePath) {
            //Load Model
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::string warn, err;

            if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str())) {
                throw FailedToOpenFileError(modelPath.c_str());
            }

            if (!warn.empty()) {
                CB_CORE_LOG_WARN("Tiny obj loader: {0}", warn);
            }
            if (!err.empty()) {
                CB_CORE_LOG_ERROR("Tiny obj loader: {0}", err);
            }

            std::unordered_map<Vertex, uint32_t> uniqueVertices{};

            for (const auto& shape : shapes) {
                for (const auto& index : shape.mesh.indices) {
                    Vertex vertex{};

                    if (index.vertex_index >= 0) {
                        vertex.Position = {
                            attrib.vertices[3 * index.vertex_index + 0],
                            attrib.vertices[3 * index.vertex_index + 1],
                            attrib.vertices[3 * index.vertex_index + 2]
                        };
                    }

                    if (index.texcoord_index >= 0) {
                        vertex.TexCoord = {
                            attrib.texcoords[2 * index.texcoord_index + 0],
                            1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                        };
                    }
                    else {
                        vertex.TexCoord = { 0.0f, 0.0f }; // Fallback UV
                    }

                    if (uniqueVertices.count(vertex) == 0) {
                        uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                        vertices.push_back(vertex);
                    }

                    indices.push_back(uniqueVertices[vertex]);
                }
            }

            Model model{};
            model.Vertices = vertices;
            model.Indices = indices;

            //Load Texture
            model.Texture = Texture::Create(texturePath);

            return model;
        }
    };

}
