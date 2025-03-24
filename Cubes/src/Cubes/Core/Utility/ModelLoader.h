#pragma once
#include "../Error/Error.h"
#include "../Renderer/Model.h"
#include "../Core.h"

#include <tiny_obj_loader.h>

namespace Cubes {

    class ModelLoader {
    public:
        static Model LoadModel(const std::string& modelPath, const std::string& texturePath);

    private:
        static std::pair<std::vector<Vertex>, std::vector<uint32_t>> LoadGeometryData(const std::string& modelPath);
        static void LoadObjDataFromFile(const std::string& modelPath, tinyobj::attrib_t* attrib, std::vector<tinyobj::shape_t>* shapes, std::vector<tinyobj::material_t>* materials);
        static std::pair<std::vector<Vertex>, std::vector<std::uint32_t>> PopulateVerticesAndIndices(tinyobj::attrib_t& attrib, std::vector<tinyobj::shape_t>& shapes);

    };

}
